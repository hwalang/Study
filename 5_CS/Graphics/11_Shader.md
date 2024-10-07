- [Shading](#shading)
- [Shader](#shader)
  - [1. Vertex Shader](#1-vertex-shader)
  - [2. Pixel Shader](#2-pixel-shader)

<br><br>

# Shading
입체감을 주기 위해서 빛과 물체가 상호작용해서 색깔을 결정하는 것, 즉 음영 처리하는 것을 shading이라 한다   
가상 공간에 있는 물체를 화면에 그릴 때, 3D에 있는 것처럼 입체감을 주기 위해 빛과 물체의 상호작용을 고려해서 음영처리하는 것이다   

<br>

# Shader
shader program( shading하는 프로그램 ) 들을 정의하는 용어   
원래는 graphics pipeline 안에서 shading을 하기 위한 프로그램으로 사용됐다   
하지만 shader가 하는 일이 많아지면서, GPU 안에서 작동할 수 있는 여러 가지 프로그램들을 shader라고 부르게 됐다   

shader program을 만들 때는 API에서 지원하는 언어가 따로 존재한다   
DirectX, Unreal, Unity에서는 High-Level Shader Language( HLSL )라는 언어를 사용한다   
OpenGL은 OpenGL Shading Language( GLSL ), Apple에서는 Metal Shading Language를 사용한다   
DirectX나 OpenGL 같은 API에서는 별도의 파일( VertexShader.hlsl )로 분리한다   
C언어를 알고 있으면 shader language를 사용하기 쉽다   

각 Shader Program을 파악하는 기본적인 방법은 `어떤 값이 들어가고, 어떤 값이 나오는지 파악`하는 것이다   
```cpp
// shader에서 공통적으로 사용하는 상수 모음
struct Constants {
  vec3 scale = vec3(1.0f);
  vec3 translation = vec3(0.0f);
  float rotationZ = 0.0f;
} g_constants;
```
위 상수를 하나로 관리하려면 matrix를 사용하면 된다   

## 1. Vertex Shader
`Graphics pipeline에서 각 vertex에 대해 개별적으로 실행되는 프로그램`이다   
기본적으로 object의 vertice를 움직여주는 GPU 프로그램이다   

이러한 `동일한 vertex shader는 특정 object의 모든 vertex에 대해 개별적으로 실행`되며, 이는 graphics pipeline의 기본 동작 방식이다   
각 vertex는 다른 vertex의 처리와 무관하게 개별적으로 처리되기 때문에 GPU는 이러한 `vertex 단위 작업을 병렬로 처리하여 높은 성능을 제공`한다   
```cpp
// simplified vertex shader

struct VSInput {
  vec3 position;    // vertex position
  vec3 color;       // vertex color
  vec2 uv;          // texture coordinate
};

struct VSOutput {
  vec3 position;
  vec3 color;
  vec2 uv;
};

VSOutput MyVertexShader(const VSInput vsInput) {
  VSOutput vsOutput;

  // TODO
  vsOutput.position = vsInput.position * g_constants.scale; // vertex를 움직이는 다양한 방법을 적용 가능
  vsOutput.color = vsInput.color;
  vsOutput.uv = vsInput.uv;

  return vsOutput;
}
```

## 2. Pixel Shader
pixel 단위로 작업하는 프로그램   
pixel에서 관심있는 데이터는 color이므로, pixel shader는 output으로 color 하나만 반환한다   
```cpp
struct PSInput {
  vec3 color;
  vec2 uv;
};

vec4 MyPixelShader(const PSInput psInput) {
  // color 작업
  return vec4(psInput.color, 1.0f);
}
```