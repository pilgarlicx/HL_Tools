#include "shared/Logging.h"

#include "OpenGL.h"

bool CBaseOpenGL::PostInitialize()
{
	if( IsPostInitialized() )
	{
		//Should only get here if it was already initalized.
		return GLEW_OK == m_GLEWResult;
	}

	m_bPostInitialized = true;

	m_GLEWResult = glewInit();

	if( m_GLEWResult != GLEW_OK )
	{
		Error( "Error initializing GLEW:\n%s\n", reinterpret_cast<const char*>( glewGetErrorString( m_GLEWResult ) ) );
	}

	return GLEW_OK == m_GLEWResult;
}

void CBaseOpenGL::GetErrors()
{
	GLenum error;

	while( ( error = glGetError() ) != GL_NO_ERROR )
	{
		Warning( "OpenGL Error: %s\n", glErrorToString( error ) );
	}
}

void glDeleteTexture( GLuint& textureId )
{
	if( textureId != GL_INVALID_TEXTURE_ID )
	{
		glDeleteTextures( 1, &textureId );
		textureId = GL_INVALID_TEXTURE_ID;
	}
}

const char* glErrorToString( const GLenum error )
{
	switch( error )
	{
	case GL_NO_ERROR:						return "GL_NO_ERROR";
	case GL_INVALID_ENUM:					return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:					return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:				return "GL_INVALID_OPERATION";
	case GL_INVALID_FRAMEBUFFER_OPERATION:	return "GL_INVALID_FRAMEBUFFER_OPERATION";
	case GL_OUT_OF_MEMORY:					return "GL_OUT_OF_MEMORY";
	case GL_STACK_UNDERFLOW:				return "GL_STACK_UNDERFLOW";
	case GL_STACK_OVERFLOW:					return "GL_STACK_OVERFLOW";

	default: return "UNKNOWN_GL_ERROR";
	}
}

const char* glFrameBufferStatusToString( const GLenum status )
{
	switch( status )
	{
	case GL_FRAMEBUFFER_COMPLETE:						return "Framebuffer complete";
	case GL_FRAMEBUFFER_UNDEFINED:						return "Framebuffer Undefined";
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			return "Framebuffer attachment incomplete";
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	return "Framebuffer missing attachment";
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			return "Framebuffer draw color attachment points undefined";
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			return "Framebuffer read color attachment points undefined";
	case GL_FRAMEBUFFER_UNSUPPORTED:					return "Framebuffer configuration unsupported";
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:			return "Framebuffer multisample configuration invalid";
	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:		return "Framebuffer layers not populated, or color attachments have incorrect textures";

	default:											return "Unknown error";
	}
}