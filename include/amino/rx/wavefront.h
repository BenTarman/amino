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


#ifndef AMINO_RX_WAVEFRONT_H
#define AMINO_RX_WAVEFRONT_H

/**
 * @file wavefront.h
 * @brief Wavefront OBJ/MTL mesh parser
 */

/* forward declaration of opaque structure
 */
struct aa_rx_wf_obj;


/**
 * Indicates an entry in a wavefront face is not used
 */
#define AA_RX_WF_OBJ_FACE_NONE -1


/**
 * Destroy the object for a wavefront obj file.
 */
AA_API void
aa_rx_wf_obj_destroy( struct aa_rx_wf_obj * );


/**
 * Return the number of MTL files
 */
AA_API size_t
aa_rx_wf_obj_mtl_count( struct aa_rx_wf_obj *obj );

/**
 * Return the ith MTL filename
 */
AA_API const char *
aa_rx_wf_obj_get_mtl_filename( struct aa_rx_wf_obj *obj, size_t i );

/**
 * Return the ith MTL struct
 */
AA_API const struct aa_rx_wf_mtl *
aa_rx_wf_obj_get_mtl( struct aa_rx_wf_obj *obj, size_t i );

/**
 * Return the number of materials
 */
AA_API size_t
aa_rx_wf_obj_material_count( struct aa_rx_wf_obj *obj );

/**
 * Return the name of the ith material
 */
AA_API const char *
aa_rx_wf_obj_get_material_name( struct aa_rx_wf_obj *obj, size_t i );

/**
 * Parse a wavefront OBJ file.
 */
AA_API struct aa_rx_wf_obj *
aa_rx_wf_parse(const char *filename);

/**
 * Retrieve the verticies
 */
AA_API void
aa_rx_wf_obj_get_vertices( const struct aa_rx_wf_obj *obj,
                           const double **verticies, size_t *n );

/**
 * Retrieve the normals
 */
AA_API void
aa_rx_wf_obj_get_normals( const struct aa_rx_wf_obj *obj,
                          const double **normals, size_t *n );

/**
 * Retrieve the vertex indices
 */
AA_API void
aa_rx_wf_obj_get_vertex_indices( const struct aa_rx_wf_obj *obj,
                                 const int32_t **v, size_t *n );

/**
 * Retrieve the normal indices
 */
AA_API void
aa_rx_wf_obj_get_normal_indices( const struct aa_rx_wf_obj *obj,
                                 const int32_t **v, size_t *n );
/**
 * Retrieve the uv indices
 */
AA_API void
aa_rx_wf_obj_get_uv_indices( const struct aa_rx_wf_obj *obj,
                             const int32_t **v, size_t *n );

/**
 * Retrieve the texture indices
 */
AA_API void
aa_rx_wf_obj_get_texture_indices( const struct aa_rx_wf_obj *obj,
                                  const int32_t **v, size_t *n );


/* forward declaration of opaque structure
 */
struct aa_rx_wf_mtl;

/* forward declaration of opaque structure
 */
struct aa_rx_wf_material;

/**
 * Parse a wavefront MTL file.
 */
AA_API struct aa_rx_wf_mtl *
aa_rx_wf_mtl_parse(const char *mtl_name );


/**
 * Destroy a wavefront MTL object.
 */
AA_API void
aa_rx_wf_mtl_destroy( struct aa_rx_wf_mtl * );

/**
 * Return the number of materials.
 */
AA_API size_t
aa_rx_wf_mtl_material_count( const struct aa_rx_wf_mtl * mtl);

/**
 * Return the i'th material.
 */
AA_API struct aa_rx_wf_material *
aa_rx_wf_mtl_get_material( const struct aa_rx_wf_mtl * mtl, size_t i);

/**
 * Does the material have a specular weight?
 */
AA_API int
aa_rx_wf_material_has_specular_weight( const struct aa_rx_wf_material * material );

/**
 * Does the material have a specular value?
 */
AA_API int
aa_rx_wf_material_has_specular( const struct aa_rx_wf_material * material );

/**
 * Does the material have an ambient value?
 */
AA_API int
aa_rx_wf_material_has_ambient( const struct aa_rx_wf_material * material );

/**
 * Does the material have an emission value?
 */
AA_API int
aa_rx_wf_material_has_emission( const struct aa_rx_wf_material * material );

/**
 * Does the material have an diffuse value?
 */
AA_API int
aa_rx_wf_material_has_diffuse( const struct aa_rx_wf_material * material );

/**
 * Does the material have an alpha value?
 */
AA_API int
aa_rx_wf_material_has_alpha( const struct aa_rx_wf_material * material );

/**
 * Does the material have an index-of-refraction value?
 */
AA_API int
aa_rx_wf_material_has_ior( const struct aa_rx_wf_material * material );

/**
 * Return the material's name.
 */
AA_API const char*
aa_rx_wf_material_get_name( const struct aa_rx_wf_material * material );

/**
 * Return the material's specular value.
 */
AA_API const double*
aa_rx_wf_material_get_specular( const struct aa_rx_wf_material * material );

/**
 * Return the material's ambient value.
 */
AA_API const double*
aa_rx_wf_material_get_ambient( const struct aa_rx_wf_material * material );

/**
 * Return the material's emission value.
 */
AA_API const double*
aa_rx_wf_material_get_emission( const struct aa_rx_wf_material * material );

/**
 * Return the material's diffuse value.
 */
AA_API const double*
aa_rx_wf_material_get_diffuse( const struct aa_rx_wf_material * material );

/**
 * Return the material's alpha value.
 */
AA_API double
aa_rx_wf_material_get_alpha( const struct aa_rx_wf_material * material );

/**
 * Return the material's index-of-refraction value.
 */
AA_API double
aa_rx_wf_material_get_ior( const struct aa_rx_wf_material * material );

#endif //AMINO_RX_WAVEFRONT_H
