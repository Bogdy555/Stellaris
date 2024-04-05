#ifndef AuroraCore_Graphics_hpp

#define AuroraCore_Graphics_hpp



#include <cstdint>
#include "AuroraCore.hpp"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>



#pragma comment(lib, "opengl32.lib")



#define WGL_FULL_ACCELERATION_ARB 0x2027
#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_ACCELERATION_ARB 0x2003

#define GL_TRUE 1
#define GL_FALSE 0
#define GL_RGB16F 0x881B
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINK_STATUS 0x8B82
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_TEXTURE_BASE_LEVEL 0x813C
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF



namespace AuroraCore
{

	namespace Graphics
	{
		namespace Assets
		{
			class Image
			{
			public:
				Image();
				Image(const Image& _Other) = delete;
				Image(Image&& _Other) noexcept;
				~Image();

				Image& operator= (const Image& _Other) = delete;
				Image& operator= (Image&& _Other) noexcept;

				bool Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount);
				bool Load(const wchar_t* _Path);
				const bool Save(const wchar_t* _Path) const;
				void Destroy();

				const size_t GetWidth() const;
				const size_t GetHeight() const;
				const size_t GetChannelsCount() const;
				uint8_t* GetData();
				const uint8_t* GetData() const;

				uint8_t& operator[] (const size_t _Index);
				const uint8_t& operator[] (const size_t _Index) const;

			private:
				size_t Width;
				size_t Height;
				size_t ChannelsCount;
				uint8_t* Data;
			};
		namespace GL
		{

			extern HMODULE DllHandle;

			extern void* (__stdcall* wglGetProcAddress)(const char*);
			extern int(__stdcall* wglChoosePixelFormatARB)(HDC, const int*, const float*, unsigned int, int*, unsigned int*);
			extern HGLRC(__stdcall* wglCreateContextAttribsARB)(HDC, HGLRC, const int*);
			extern int(__stdcall* wglSwapIntervalEXT)(int);
			extern void(__stdcall* glViewport)(int, int, int, int);
			extern void(__stdcall* glClearColor)(float, float, float, float);
			extern void(__stdcall* glClear)(unsigned int);
			extern void(__stdcall* glUseProgram)(unsigned int);
			extern void(__stdcall* glBindVertexArray)(unsigned int);
			extern void(__stdcall* glDrawElements)(unsigned int, int, unsigned int, const void*);
			extern void(__stdcall* glEnable)(unsigned int);
			extern void(__stdcall* glDisable)(unsigned int);
			extern void(__stdcall* glBlendFunc)(unsigned int, unsigned int);
			extern void(__stdcall* glDepthFunc)(unsigned int);
			extern void(__stdcall* glGenBuffers)(int, unsigned int*);
			extern void(__stdcall* glBindBuffer)(unsigned int, unsigned int);
			extern void(__stdcall* glBufferData)(unsigned int, intptr_t, const void*, unsigned int);
			extern void(__stdcall* glGenVertexArrays)(int, unsigned int*);
			extern void(__stdcall* glEnableVertexAttribArray)(unsigned int);
			extern void(__stdcall* glVertexAttribPointer)(unsigned int, int, unsigned int, unsigned char, int, const void*);
			extern unsigned int(__stdcall* glCreateProgram)();
			extern unsigned int(__stdcall* glCreateShader)(unsigned int);
			extern void(__stdcall* glShaderSource)(unsigned int, int, const char* const*, int*);
			extern void(__stdcall* glCompileShader)(unsigned int);
			extern void(__stdcall* glAttachShader)(unsigned int, unsigned int);
			extern void(__stdcall* glLinkProgram)(unsigned int);
			extern void(__stdcall* glValidateProgram)(unsigned int);
			extern int(__stdcall* glGetUniformLocation)(unsigned int, const char*);
			extern void(__stdcall* glUniform1f)(int, float);
			extern void(__stdcall* glUniform2f)(int, float, float);
			extern void(__stdcall* glUniform3f)(int, float, float, float);
			extern void(__stdcall* glUniform4f)(int, float, float, float, float);
			extern void(__stdcall* glUniform1i)(int, int);
			extern void(__stdcall* glUniform2i)(int, int, int);
			extern void(__stdcall* glUniform3i)(int, int, int, int);
			extern void(__stdcall* glUniform4i)(int, int, int, int, int);
			extern void(__stdcall* glUniform1ui)(int, int);
			extern void(__stdcall* glUniformMatrix2fv)(int, int, unsigned char, const float*);
			extern void(__stdcall* glUniformMatrix3fv)(int, int, unsigned char, const float*);
			extern void(__stdcall* glUniformMatrix4fv)(int, int, unsigned char, const float*);
			extern void(__stdcall* glDetachShader)(unsigned int, unsigned int);
			extern void(__stdcall* glDeleteBuffers)(int, unsigned int*);
			extern void(__stdcall* glDeleteVertexArrays)(int, unsigned int*);
			extern void(__stdcall* glDisableVertexAttribArray)(unsigned int);
			extern void(__stdcall* glDeleteProgram)(unsigned int);
			extern void(__stdcall* glDeleteShader)(unsigned int);
			extern void(__stdcall* glGetShaderiv)(unsigned int, unsigned int, int*);
			extern void(__stdcall* glGetShaderInfoLog)(unsigned int, int, int*, char*);
			extern void(__stdcall* glGetProgramiv)(unsigned int, unsigned int, int*);
			extern void(__stdcall* glGetProgramInfoLog)(unsigned int, int, int*, char*);
			extern void(__stdcall* glGenTextures)(int, unsigned int*);
			extern void(__stdcall* glBindTexture)(unsigned int, unsigned int);
			extern void(__stdcall* glTexParameteri)(unsigned int, unsigned int, int);
			extern void(__stdcall* glTexImage2D)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*);
			extern void(__stdcall* glActiveTexture)(unsigned int);
			extern void(__stdcall* glDeleteTextures)(int, unsigned int*);
			extern void(__stdcall* glCullFace)(unsigned int);
			extern void(__stdcall* glFrontFace)(unsigned int);
			extern void(__stdcall* glGenerateMipmap)(unsigned int);

			bool Load();
			void Unload();


		}

	}

}



#endif
