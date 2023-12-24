/*
 *  <Short Description>
 *  Copyright (C) 2023  Brett Terpstra
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* comment */

#ifndef GL_DOC_GENERATOR_TEST_H
#define GL_DOC_GENERATOR_TEST_H

/**
* @name glDrawTransformFeedbackStream - render primitives using a count derived from a specifed stream of a transform feedback object
* @usage
* @code void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream); @endcode
* @param mode Specifies what kind of primitives to render. Symbolic constants <b>GL_POINTS</b>, <b>GL_LINE_STRIP</b>, <b>GL_LINE_LOOP</b>,
*             <b>GL_LINES</b>, <b>GL_LINE_STRIP_ADJACENCY</b>, <b>GL_LINES_ADJACENCY</b>, <b>GL_TRIANGLE_STRIP</b>, <b>GL_TRIANGLE_FAN</b>,
*             <b>GL_TRIANGLES</b>, <b>GL_TRIANGLE_STRIP_ADJACENCY</b>, <b>GL_TRIANGLES_ADJACENCY</b>, and <b>GL_PATCHES</b>
*             are accepted.
* @param id Specifies the name of a transform feedback object from which to retrieve a primitive count.
* @param stream Specifies the index of the transform feedback stream from which to retrieve a primitive count.
*
* @errors GL_INVALID_ENUM is generated if mode is not an accepted value.
* @errors GL_INVALID_VALUE is generated if id is not the name of a transform feedback object.
* @errors GL_INVALID_VALUE is generated if stream is greater than or equal to the value of GL_MAX_VERTEX_STREAMS.
* @errors GL_INVALID_OPERATION is generated if a non-zero buffer object name is bound to an enabled array and the buffer object's
*         data store is currently mapped.
* @errors GL_INVALID_OPERATION is generated if a geometry shader is active and mode is incompatible with the input primitive type
*         of the geometry shader in the currently installed program object.
* @errors GL_INVALID_OPERATION is generated if mode is GL_PATCHES and no tessellation control shader is active.
* @errors GL_INVALID_OPERATION is generated if  glEndTransformFeedback has never been called while the transform feedback object named
*         by id was bound.
*
*/
#define glDrawTransformFeedbackStream glad_glDrawTransformFeedbackStream

int ident = 0;

// TODO:
typedef void (*glCopyTextureSubImage3D)(int n, const int * pipelines);

/**
* @name glUniform - Specify the value of a uniform variable for the current program object
* @usage
* @param location Specifies the location of the uniform variable to be modified.
* @param count For the vector (<b>glUniform*v</b>) commands, specifies the number of elements that are to be modified. This should be 1
*              if the targeted uniform variable is not an array, and 1 or more if it is an array.
* @param transpose For the matrix commands, specifies whether to transpose the matrix as the values are loaded into the uniform variable.
* @param v0,            v1,            v2,            v3 For the scalar commands, specifies the new values to be used for the specified uniform variable.
* @param value For the vector and matrix commands, specifies a pointer to an array of <em class="parameter"><b>count</b></em> values that
*              will be used to update the specified uniform variable.
* @note glUniform1i and glUniform1iv are the only two functions that may be used to load uniform variables defined as sampler types.
*       Loading samplers with any other function will result in a GL_INVALID_OPERATION error.
* @note If count is greater than 1 and the indicated uniform variable is not an array, a GL_INVALID_OPERATION error is generated
*       and the specified uniform variable will remain unchanged.
* @note Other than the preceding exceptions, if the type and size of the uniform variable as defined in the shader do not match
*       the type and size specified in the name of the command used to load its value, a GL_INVALID_OPERATION error will be generated
*       and the specified uniform variable will remain unchanged.
* @note If location is a value other than -1 and it does not represent a valid uniform variable location in the current program
*       object, an error will be generated, and no changes will be made to the uniform variable storage of the current program object.
*       If location is equal to -1, the data passed in will be silently ignored and the specified uniform variable will not
*       be changed.
*
* @errors GL_INVALID_OPERATION is generated if there is no current program object.
* @errors GL_INVALID_OPERATION is generated if the size of the uniform variable declared in the shader does not match the size indicated
*         by the glUniform command.
* @errors GL_INVALID_OPERATION is generated if one of the signed or unsigned integer variants of this function is used to load a uniform
*         variable of type float, vec2, vec3, vec4, or an array of these, or if one of the floating-point variants of this
*         function is used to load a uniform variable of type int, ivec2, ivec3, ivec4, unsigned int, uvec2, uvec3, uvec4, or an array
*         of these.
* @errors GL_INVALID_OPERATION is generated if one of the signed integer variants of this function is used to load a uniform variable
*         of type unsigned int, uvec2, uvec3, uvec4, or an array of these.
* @errors GL_INVALID_OPERATION is generated if one of the unsigned integer variants of this function is used to load a uniform variable
*         of type int, ivec2, ivec3, ivec4, or an array of these.
* @errors GL_INVALID_OPERATION is generated if location is an invalid uniform location for the current program object and location
*         is not equal to -1.
* @errors GL_INVALID_VALUE is generated if count is less than 0.
* @errors GL_INVALID_OPERATION is generated if count is greater than 1 and the indicated uniform variable is not an array variable.
* @errors GL_INVALID_OPERATION is generated if a sampler is loaded using a command other than glUniform1i and glUniform1iv.
*
*/
#define glUniform1d glad_glUniform1d

/**
* @name glUniform - Specify the value of a uniform variable for the current program object
* @usage
* @param location Specifies the location of the uniform variable to be modified.
* @param count For the vector (<b>glUniform*v</b>) commands, specifies the number of elements that are to be modified. This should be 1
*              if the targeted uniform variable is not an array, and 1 or more if it is an array.
* @param transpose For the matrix commands, specifies whether to transpose the matrix as the values are loaded into the uniform variable.
* @param v0,            v1,            v2,            v3 For the scalar commands, specifies the new values to be used for the specified uniform variable.
* @param value For the vector and matrix commands, specifies a pointer to an array of <em class="parameter"><b>count</b></em> values that
*              will be used to update the specified uniform variable.
* @note glUniform1i and glUniform1iv are the only two functions that may be used to load uniform variables defined as sampler types.
*       Loading samplers with any other function will result in a GL_INVALID_OPERATION error.
* @note If count is greater than 1 and the indicated uniform variable is not an array, a GL_INVALID_OPERATION error is generated
*       and the specified uniform variable will remain unchanged.
* @note Other than the preceding exceptions, if the type and size of the uniform variable as defined in the shader do not match
*       the type and size specified in the name of the command used to load its value, a GL_INVALID_OPERATION error will be generated
*       and the specified uniform variable will remain unchanged.
* @note If location is a value other than -1 and it does not represent a valid uniform variable location in the current program
*       object, an error will be generated, and no changes will be made to the uniform variable storage of the current program object.
*       If location is equal to -1, the data passed in will be silently ignored and the specified uniform variable will not
*       be changed.
*
* @errors GL_INVALID_OPERATION is generated if there is no current program object.
* @errors GL_INVALID_OPERATION is generated if the size of the uniform variable declared in the shader does not match the size indicated
*         by the glUniform command.
* @errors GL_INVALID_OPERATION is generated if one of the signed or unsigned integer variants of this function is used to load a uniform
*         variable of type float, vec2, vec3, vec4, or an array of these, or if one of the floating-point variants of this
*         function is used to load a uniform variable of type int, ivec2, ivec3, ivec4, unsigned int, uvec2, uvec3, uvec4, or an array
*         of these.
* @errors GL_INVALID_OPERATION is generated if one of the signed integer variants of this function is used to load a uniform variable
*         of type unsigned int, uvec2, uvec3, uvec4, or an array of these.
* @errors GL_INVALID_OPERATION is generated if one of the unsigned integer variants of this function is used to load a uniform variable
*         of type int, ivec2, ivec3, ivec4, or an array of these.
* @errors GL_INVALID_OPERATION is generated if location is an invalid uniform location for the current program object and location
*         is not equal to -1.
* @errors GL_INVALID_VALUE is generated if count is less than 0.
* @errors GL_INVALID_OPERATION is generated if count is greater than 1 and the indicated uniform variable is not an array variable.
* @errors GL_INVALID_OPERATION is generated if a sampler is loaded using a command other than glUniform1i and glUniform1iv.
*
*/
#define glUniform glad_glUniform1d

/**
* @name glDrawTransformFeedbackStream - render primitives using a count derived from a specifed stream of a transform feedback object
* @usage
* @code void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream); @endcode
* @param mode Specifies what kind of primitives to render. Symbolic constants <b>GL_POINTS</b>, <b>GL_LINE_STRIP</b>, <b>GL_LINE_LOOP</b>,
*             <b>GL_LINES</b>, <b>GL_LINE_STRIP_ADJACENCY</b>, <b>GL_LINES_ADJACENCY</b>, <b>GL_TRIANGLE_STRIP</b>, <b>GL_TRIANGLE_FAN</b>,
*             <b>GL_TRIANGLES</b>, <b>GL_TRIANGLE_STRIP_ADJACENCY</b>, <b>GL_TRIANGLES_ADJACENCY</b>, and <b>GL_PATCHES</b>
*             are accepted.
* @param id Specifies the name of a transform feedback object from which to retrieve a primitive count.
* @param stream Specifies the index of the transform feedback stream from which to retrieve a primitive count.
*
* @errors GL_INVALID_ENUM is generated if mode is not an accepted value.
* @errors GL_INVALID_VALUE is generated if id is not the name of a transform feedback object.
* @errors GL_INVALID_VALUE is generated if stream is greater than or equal to the value of GL_MAX_VERTEX_STREAMS.
* @errors GL_INVALID_OPERATION is generated if a non-zero buffer object name is bound to an enabled array and the buffer object's
*         data store is currently mapped.
* @errors GL_INVALID_OPERATION is generated if a geometry shader is active and mode is incompatible with the input primitive type
*         of the geometry shader in the currently installed program object.
* @errors GL_INVALID_OPERATION is generated if mode is GL_PATCHES and no tessellation control shader is active.
* @errors GL_INVALID_OPERATION is generated if  glEndTransformFeedback has never been called while the transform feedback object named
*         by id was bound.
*
*/
void glDrawTransformFeedbackStream()
{

}

void func1()
{

}

void


func2
        
        ()
{

}

void func3
        ()
{

}

#endif //GL_DOC_GENERATOR_TEST_H
