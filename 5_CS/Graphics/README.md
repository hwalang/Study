- [Basic](#basic)
- [Graphics 1 : Ray\_Tracing](#graphics-1--ray_tracing)
- [Graphics 2 : Rasterization](#graphics-2--rasterization)

<br>

**[Computer Graphics 자료 - scratchapixel](https://www.scratchapixel.com/index.html)**   
생소한 용어가 많기 때문에 일단 메모한 뒤에 나중에 자세히 알아본다   


# Basic
1. [Vector Operation](Vector_Operation.md)
   - scalar와 vector, `magnitude`, `normalize(unit vector)`
   - `Dot / Cross product`
   - glm::vec3
2. [Point Operation](Point_Operation.md)
   - `line`, `line-segment`
   - Affine, `Affine Combination( Affine, Sum )`
3. [Nonlinear Transformation](Nonlinear_Transformation.md)
   - perspective projection


<br><br>


# Graphics 1 : Ray_Tracing
1. **[DirectX11 환경 설정](0_DirectX11_환경설정.md)**
   - vcpkg( imgui, glm )
2. **[Digital_Image_Basics](1_Digital_Image_Basics.md)**
   - Digital Image( `Grayscale Image`, `Color Image` )
   - `pixel intensity`( image intensity, amplitude value )
   - `resolution`
   - `Stored Image Size`
   - `channel`
   - `color space conversion`, `image compression`, `Luminance`, `Chrominance`
3. **[Bloom Effect](2_Bloom_Effect.md)**
   - `kernel`( filter ), `convolution, seperable convolution`
   - box `blur`, gaussian blur
   - `Relative Luminance Y`, `bloom effect`
4. **[Coordinate Systems](3_Coordinate_Systems.md)**
   - `Texture Coordinates`
     - texture`
     - `texel`
     - **`texel mapping process`**
     - primitive
     - object space
   - `Bary-Centric Coordinates`, 
     - `Edge Function`과 Cross Product
5. **[Lighting Model](4_Lighting_Model.md)**
   - `Lambertian Reflection`
     - `Diffuse Surface`, `Diffuse Reflection`, `Specular Reflection`, `Lambert's consine law`, `Diffuse Lighting Model`
   - `Phong Reflection Model`
     - Diffuse, Specular, Ambient
   - `Blinn-Phong Model`
     - Halfway Vector
6. **[Ray Tracing](5_Ray_Tracing.md)**
   - rendering( `image-order, object-order` )
   - `Ray Tracing Algorithm`
   - `Ray-sphere intersection`
   - `Triangular Mesh`
   - `Shadow`
   - `Reflection`
   - `Transparency`, `Refraction`
   - `Cube Mapping`
7. **[Texturing](6_texturing.md)**
   - `texture coordinates`
   - `sampling`, `exture sampling
8.  **[Anti Aliasing](7_Anti_Aliasing.md)**
   - `super sampling`


<br><br>


# Graphics 2 : Rasterization
1. **[Rasterization](8_Rasterization.md)**
   - Triangle Model
   - `Ray Tracing VS Rasterization`
   - `Bounding Box`
2. **[Transformation](9_Transformation.md)**
   - `GPU 특징`
   - Clockwise Winding Order
   - Graphics: `Triangle Mesh를 위한 Data Structure`
   - `2D Transformation`
     - Translate
     - Rotate
     - Scale
   - `Vertex Shader`
3. **[Depth Buffer( z-buffer )](10_Depth_Buffer.md)**
   - Depth Buffer `in Orthographic Projection`
4. **[Shader](11_Shader.md)**
   - Shading
   - Shader
   - `Vertex Shader`
   - `Pixel Shader`
5. **[Culling](12_Culling.md)**
   - `Back-face Culling`
6. [Projection](13_Projection.md)
   - `Orthographics`
   - `Perspective`, `Perspective-Correct Interpolation`

<br>

복잡한 로직( 예, 파이어볼 )을 디버깅 할 때는 일부 이미지 처리 효과나 이펙트 등 유닛 테스트처럼 따로 분리해서 디버깅하는 것을 권장한다   
일반적으로 일효율을 높이는 요령이다   