생소한 용어가 많기 때문에 일단 메모한 뒤에 나중에 자세히 알아본다<br>

# Index
1. [DirectX11 환경 설정](0_DirectX11_환경설정.md)
   - vcpkg( imgui, glm )
2. [Digital_Image_Basics](1_Digital_Image_Basics.md)
   - Digital Image( `Grayscale Image`, `Color Image` )
   - `pixel intensity`( image intensity, amplitude value )
   - `resolution`
   - `Stored Image Size`
   - `channel`
   - `color space conversion`, `image compression`, `Luminance`, `Chrominance`
3. [Bloom Effect](2_Bloom_Effect.md)
   - `kernel`( filter ), `convolution, seperable convolution`
   - box `blur`, gaussian blur
   - `Relative Luminance Y`, `bloom effect`
4. [Coordinate Systems](4_Coordinate_Systems.md)
   - `texture`, `texel`, `Texture Coordinates`, **`texel mapping process`**, primitive, object space
5. [Phong Model](4_Phong_Model.md)
   - `light effect`
   - `Lambertian Reflection`
6. [Ray Tracing](5_Ray_Tracing.md)
   - rendering( `image-order, object-order` )
   - `Ray Tracing Algorithm`
   - `Ray-sphere intersection`
   - `Triangular Mesh`
   - `Shadow`
   - `Reflection`
   - `Transparency`, `Refraction`
   - `Cube Mapping`
   - projection( `Orthographic, Perspective` )
7. [Texturing](6_texturing.md)
   - `texture coordinates`
   - `sampling`, `exture sampling
8.  [Anti Aliasing](7_Anti_Aliasing.md)
   - `super sampling`
---
### Basic
1. [Vector Operation](Vector_Operation.md)
   - scalar와 vector, `magnitude`, `normalize(unit vector)`
   - `Dot / Cross product`
   - glm::vec3
2. [Point Operation](Point_Operation.md)
   - `line`, `line-segment`
   - Affine, `Affine Combination( Affine, Sum )`

<br>

Backface culling: 뒷면을 그리지 않는 방법<br>