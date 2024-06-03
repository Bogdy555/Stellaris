#ifndef AuroraCore_Graphics_hpp

#define AuroraCore_Graphics_hpp



#include "AuroraCore.hpp"



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
				// Testat doar cu 24 bit bitmaps fara palete de culori. Pentru restul cazurilor undefined behaviour
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
		}

		namespace GL
		{

			// DLL OpenGL
			extern HMODULE DllHandle;

			// Functii din driver
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

			class Context
			{

			public:

				Context();
				Context(const Context& _Other) = delete;
				Context(Context&& _Other) noexcept;
				~Context();

				bool Create(Window& _WndPtr);
				void Destroy();
				bool Bind();

				const HGLRC GetHandle() const;

				Window* GetWndPtr();
				const Window* GetWndPtr() const;

				operator const HGLRC() const;

				void operator= (const Context& _Other) = delete;
				void operator= (Context&& _Other) noexcept;

				static void Unbind();

			private:

				HGLRC Handle;
				Window* WndPtr;

			};

			struct VertexData
			{
				Math::Vec3f Position = Math::Vec3f(0.0f, 0.0f, 0.0f);
				Math::Vec4f Color = Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
				Math::Vec2f TextureCoords = Math::Vec2f(0.0f, 0.0f);
			};

			typedef std::vector<VertexData> VertexBufferCPUCash;

			class VertexBuffer
			{

			public:

				VertexBuffer();
				VertexBuffer(const VertexBuffer& _Other) = delete;
				VertexBuffer(VertexBuffer&& _Other) noexcept;
				~VertexBuffer();

				bool Create(const VertexBufferCPUCash& _VBO_CPUCash);
				void Destroy();
				bool Bind();

				const bool CheckCreated() const;
				const unsigned int GetID() const;

				void operator= (const VertexBuffer& _Other) = delete;
				void operator= (VertexBuffer&& _Other) noexcept;

				static void Unbind();

			private:

				unsigned int ID;

			};

			typedef std::vector<unsigned int> IndexBufferCPUCash;

			class IndexBuffer
			{

			public:

				IndexBuffer();
				IndexBuffer(const IndexBuffer& _Other) = delete;
				IndexBuffer(IndexBuffer&& _Other) noexcept;
				~IndexBuffer();

				bool Create(const IndexBufferCPUCash& _IBO_CPUCash);
				void Destroy();
				bool Bind();

				const bool CheckCreated() const;
				const unsigned int GetID() const;

				void operator= (const IndexBuffer& _Other) = delete;
				void operator= (IndexBuffer&& _Other) noexcept;

				static void Unbind();

			private:

				unsigned int ID;

			};

			// E necesara pastrarea CPU cash ului in memorie pentru a putea randa mai tarziu (sau cel putin dimensiunea in elemente a IBO ului)
			struct MeshCPUCash
			{
				VertexBufferCPUCash VBO;
				IndexBufferCPUCash IBO;
			};

			struct Mesh
			{
				VertexBuffer VBO;
				IndexBuffer IBO;
			};

			class VertexAttribArray
			{

			public:

				VertexAttribArray();
				VertexAttribArray(const VertexAttribArray& _Other) = delete;
				VertexAttribArray(VertexAttribArray&& _Other) noexcept;
				~VertexAttribArray();

				bool Create();
				void Destroy();
				bool Bind();
				bool EnableAttrib(unsigned int _AttribID, int _ElementsCount, int _ElementsCountTotal, size_t _Offset);
				bool DisableAttrib(unsigned int _AttribID);

				const bool CheckCreated() const;
				const unsigned int GetID() const;

				void operator= (const VertexAttribArray& _Other) = delete;
				void operator= (VertexAttribArray&& _Other) noexcept;

				static void Unbind();

			private:

				unsigned int ID;

			};

			class Shader
			{

			public:

				Shader();
				Shader(const Shader& _Other) = delete;
				Shader(Shader&& _Other) noexcept;
				~Shader();

				bool Create(const char* _VS, const char* _FS);
				void Destroy();
				bool Bind();

				const bool CheckCreated() const;
				const unsigned int GetID() const;

				void operator= (const Shader& _Other) = delete;
				void operator= (Shader&& _Other) noexcept;

				static void Unbind();

			private:

				unsigned int ID;

			};

			class Uniform
			{

			public:

				Uniform();
				Uniform(const Uniform& _Other) = delete;
				Uniform(Uniform&& _Other) noexcept;
				~Uniform();

				bool GetLocation(const Shader& _Shader, const char* _Name);
				void ReleaseLocation();

				const bool CheckBind() const;
				const int GetID() const;

				bool Set1f(float _x);
				bool Set2f(float _x, float _y);
				bool Set3f(float _x, float _y, float _z);
				bool Set4f(float _x, float _y, float _z, float _w);

				bool Set1i(int _x);
				bool Set2i(int _x, int _y);
				bool Set3i(int _x, int _y, int _z);
				bool Set4i(int _x, int _y, int _z, int _w);

				bool Set1b(bool _Value);

				bool Set1ui(unsigned int _Value);

				bool SetMatrix2fv(float* _Data);
				bool SetMatrix3fv(float* _Data);
				bool SetMatrix4fv(float* _Data);

				void operator= (const Uniform& _Other) = delete;
				void operator= (Uniform&& _Other) noexcept;

			private:

				int ID;

			};

			// Format RGBA UINT8 cu repeat si nearest filtering
			class Texture2D
			{

			public:

				Texture2D();
				Texture2D(const Texture2D& _Other) = delete;
				Texture2D(Texture2D&& _Other) noexcept;
				~Texture2D();

				bool Create(const Assets::Image& _TexData);
				void Destroy();
				bool Bind();

				const bool CheckCreated() const;
				const unsigned int GetID() const;

				void operator= (const Texture2D& _Other) = delete;
				void operator= (Texture2D&& _Other) noexcept;

				static void Unbind();

			private:

				unsigned int ID;

			};

			struct CameraStruct
			{
				Math::Vec2f Position = Math::Vec2f(0.0f, 0.0f);
				float Angle = 0.0f;
				float Fov = 10.0f;
				float ZNear = -1.0f; // Pentru layered rendering
				float ZFar = 1.0f; // Pentru layered rendering
			};

			// Cunoscut si sub numele de transform
			struct MeshWorldDataStruct
			{
				Math::Vec3f Position = Math::Vec3f(0.0f, 0.0f, 0.0f);
				float Angle = 0.0f;
				Math::Vec2f Scale = Math::Vec2f(1.0f, 1.0f);
			};

			struct MaterialStruct
			{
				int TextureAlbedo = 0;
				Math::Vec4f Color = Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
				// Mecanism de indexare in sprite sheet uri
				Math::Vec2f Start = Math::Vec2f(0.0f, 0.0f);
				Math::Vec2f Size = Math::Vec2f(1.0f, 1.0f);
			};

			// Helpere pentru a pasa uniforme catre GPU cu aceasi structura ca mai sus

			const std::string GetUniformIndexName(const std::string _Name, const size_t _Index);
			bool UniformSetCamera(const CameraStruct& _Camera, const Shader& _Shader, const char* _Name);
			bool UniformSetMeshWorldData(const MeshWorldDataStruct& _MeshWorldData, const Shader& _Shader, const char* _Name);
			bool UniformSetMaterial(const MaterialStruct& _Material, const Shader& _Shader, const char* _Name);

			Math::Mat4f GetProjectionFromCamera(const CameraStruct& _CameraStr, const float _AspectRatio);
			Math::Mat4f GetViewFromCamera(const CameraStruct& _CameraStr);
			Math::Mat4f GetModelFromWorldData(const MeshWorldDataStruct& _WorldData);

		}

	}

}



#endif
