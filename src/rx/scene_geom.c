/* -*- mode: C; c-basic-offset: 4; -*- */
/* ex: set shiftwidth=4 tabstop=4 expandtab: */
/*
 * Copyright (c) 2015, Rice University
 * All rights reserved.
 *
 * Author(s): Neil T. Dantam <ntd@rice.edu>
 *
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of copyright holder the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "amino.h"
#include "amino/rx/scenegraph.h"
#include "amino/rx/scenegraph_internal.h"
#include "amino/rx/scene_geom.h"
#include "amino/rx/scene_geom_internal.h"
#include "sg_convenience.h"

#define ALLOC_GEOM(TYPE, var, type_value, geom_opt, sg, frame)  \
    TYPE *var = AA_NEW0(TYPE);                                  \
    AA_MEM_CPY(&g->base.opt, geom_opt, 1);                      \
    var->base.type = type_value;                                \
    var->base.gl_buffers = NULL;                                \
    var->base.refcount = 1;

//aa_rx_sg_add_geom(sg, frame, &var->base);

struct aa_rx_geom *
aa_rx_geom_box (
    struct aa_rx_geom_opt *opt,
    const double dimension[3] )
{
    ALLOC_GEOM( struct aa_rx_geom_box, g,
                AA_RX_BOX, opt,
                scene_graph, frame );
    AA_MEM_CPY(g->shape.dimension, dimension, 3);
    return &g->base;
}

struct aa_rx_geom *
aa_rx_geom_sphere (
    struct aa_rx_geom_opt *opt,
    double radius )
{
    ALLOC_GEOM( struct aa_rx_geom_sphere, g,
                AA_RX_SPHERE, opt,
                scene_graph, frame );
    g->shape.radius = radius;
    return &g->base;
}

struct aa_rx_geom *
aa_rx_geom_cylinder (
    struct aa_rx_geom_opt *opt,
    double height,
    double radius )
{
    ALLOC_GEOM( struct aa_rx_geom_cylinder, g,
                AA_RX_CYLINDER, opt,
                scene_graph, frame );
    g->shape.radius = radius;
    g->shape.height = height;
    return &g->base;
}

struct aa_rx_geom *
aa_rx_geom_cone (
    struct aa_rx_geom_opt *opt,
    double height,
    double start_radius,
    double end_radius )
{
    ALLOC_GEOM( struct aa_rx_geom_cone, g,
                AA_RX_CONE, opt,
                scene_graph, frame );
    g->shape.start_radius = start_radius;
    g->shape.end_radius = end_radius;
    g->shape.height = height;
    return &g->base;
}


void
aa_rx_geom_attach (
    struct aa_rx_sg *sg,
    const char *frame,
    struct aa_rx_geom *geom )
{
    aa_rx_sg_add_geom(sg, frame, geom);
}

struct aa_rx_geom *
aa_rx_geom_copy( struct aa_rx_geom *src )
{
    src->refcount++;
    return src;
}

void
aa_rx_geom_destroy( struct aa_rx_geom *geom )
{

    geom->refcount--;
    if( 0 == geom->refcount )
    {
        free(geom);
    }
}

void *
aa_rx_geom_shape ( const struct aa_rx_geom *g,
                   enum aa_rx_geom_shape *shape_type )
{
    void *shape = NULL;
    switch(g->type ) {
    case AA_RX_NOSHAPE: break;
    case AA_RX_MESH:
        shape = &((struct aa_rx_geom_mesh*)g)->shape;
        break;
    case AA_RX_BOX:
        shape = &((struct aa_rx_geom_box*)g)->shape;
        break;
    case AA_RX_SPHERE:
        shape = &((struct aa_rx_geom_sphere*)g)->shape;
        break;
    case AA_RX_CYLINDER:
        shape = &((struct aa_rx_geom_cylinder*)g)->shape;
        break;
    case AA_RX_CONE:
        shape = &((struct aa_rx_geom_cone*)g)->shape;
        break;
    }
    if( shape_type ) *shape_type = g->type;
    return shape;
}
