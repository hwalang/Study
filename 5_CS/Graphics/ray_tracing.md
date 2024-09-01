- [Introduce](#introduce)
  - [3D 장면을 2D 화면에 rendering 하는 2가지 방법](#3d-장면을-2d-화면에-rendering-하는-2가지-방법)
    - [1. object-order rendering](#1-object-order-rendering)
    - [2. image-order rendering](#2-image-order-rendering)
    - [3. 차이점](#3-차이점)
- [Ray Tracing Algorithm](#ray-tracing-algorithm)
- [Projection](#projection)
- [Ray-Sphere Intersection](#ray-sphere-intersection)
  - [Ray-Tracing에 사용하는 3가지 경우](#ray-tracing에-사용하는-3가지-경우)
    - [1. Object와 Ray의 충돌 검출](#1-object와-ray의-충돌-검출)
    - [2. Ray 굴절 및 반사 계산](#2-ray-굴절-및-반사-계산)
    - [3. Shadow 계산](#3-shadow-계산)
- [Ray Tracing을 구현하기 위해 필요한 정보](#ray-tracing을-구현하기-위해-필요한-정보)
    - [1. Ray( 광선 정보 )](#1-ray-광선-정보-)
    - [2. Hit( 충돌 정보 )](#2-hit-충돌-정보-)
    - [3. Ray Tracer( rendering에 필요한 정보 )](#3-ray-tracer-rendering에-필요한-정보-)

<br>

[Ray Tracing 참고 blog](https://velog.io/@tjswodud/%EA%B7%B8%EB%9E%98%ED%94%BD%EC%8A%A4-4.-%EB%A0%88%EC%9D%B4%ED%8A%B8%EB%A0%88%EC%9D%B4%EC%8B%B1)<br>
[ wiki Ray Tracing ](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))<br>

<br>

# Introduce
기본적으로 `rendering은 입력으로 object의 집합을 받아 출력으로 pixel 배열을 생성하는 과정`이다<br>

<br>

## 3D 장면을 2D 화면에 rendering 하는 2가지 방법
object( 3D )가 pixel( 2D )에 접근하는 2가지 주요 방식이 존재한다<br>

### 1. object-order rendering
각 `object`는 순서대로 다뤄지고, object마다 영향을 미치는 모든 pixel을 찾고 업데이트한다<br>

장면의 복잡성이 적은 경우에 효율적이다.<br>

### 2. image-order rendering
각 `pixel`은 순서대로 다뤄지며 pixel마다 영향을 미치는 모든 object를 찾고 pixel 값을 계산한다<br>

장면의 복잡성이 높은 경우에 효율적이다<br>

image-order rendering은 작업이 단순하고 유연하게 effect를 생성할 수 있으며, 비슷한 image를 만드는 데 걸리는 시간이 훨씬 길다<br>
`Ray-Tracing은 3D 컴퓨터 그래픽에서 디지털 이미지 rendering을 위한 image-order algorithm`이다<br>

### 3. 차이점
두 방법은 같은 이미지를 연산할 수 있지만, `서로 다른 종류의 effect를 계산하는데 적합`하며, `전혀 다른 성능`을 보여준다<br>

<br>
<br>

# Ray Tracing Algorithm
`Ray Tracing은 3D 컴퓨터 그래픽에서 사실적인 이미지를 제작하는 방법`이다<br>
광선을 추적하여 광선이 물체와 상호작용하는 방식에 초점을 둔다<br>

![alt text](Images/Ray_Tracing.png)<br>

Scene Object를 Screen에 비추기 위해서 어떻게 할까?<br>

<br>

1. **Ray Casting( 광선 발사 )**
   - Camera가 바라보는 방향으로 `모든 pixel에서 Scene으로 pixel 1개당 하나의 Ray를 쏜다`<br>
   - 나중에는 각 pixel에서 여러 개의 Ray를 Scene으로 쏘는 경우도 있다.
2. **Intersection Calculation( object와 교차점 계산 )**
   - Ray가 처음으로 충돌한( hit ) 지점( point )을 찾는다.
   - `Ray가 Object와 교차하는 지점을 찾는다.`
3. **Ray-Object Interaction( 상호작용 )**
   - 교`차 지점에서 object의 surface 속성( 반사, 굴절, 그림자 등 )을 계산하여 pixel 값을 결정`한다.
4. **Lighting and Shading( 빛과의 상호작용 )**
   - Ray와의 관계를 통해 조명과 그림자 효과를 적용한다<br>
5. **Screen**
   - Screen에 계산한 pixel 값을 적용한다

<br>

`Ray의 방향`은 DirectX에서는 `+Z방향( Left-handed Systems )`이다.<br>

가상의 눈에서 가상 화면의 각 pixel을 통과하는 경로를 추적하고, 이를 통해 보이는 object의 색상을 계산하는 방식이다<br>
먼저 빛이 screen을 통과하면 가장 가까운 object를 식별한다.<br>
object를 식별하면 ray tracing 알고리즘을 통해 screen에 보일 pixel 값을 정한다.<br>
pixel 값은 object의 재질, 광원을 결합하여 최종 pixel( 색상 ) 값을 결정한다<br>

<br>
<br>

# Projection
Orthographic Projection( 정투영 )과 Perspective Projection( 원근투영 )이 있다<br>
Ray를 Screen에 수직인 방향( vec3(0, 0, 1) )으로 쏴주는 것을 Orthographic projection이라 한다<br>

<br>
<br>

# Ray-Sphere Intersection
[ wiki - Line-Sphere Intersection ](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection)<br>

Line-Sphere Intersection은 `3D 공간에 주어진 직선과 구가 만나는 지점을 찾을 때 이용`하는 개념이다<br>

![<alt text>](Images/ray_sphere_intersection.png)<br>


Line과 Sphere는 3가지 방법으로 상호작용한다<br>

1. No Intersection
2. Point Intersection
3. Two point Intersection

<br>

이러한 상황을 구별하는 것은 Ray-Tracing 알고리즘의 일반적인 연산에서 유용하다<br>
위 Ray-Tracing 알고리즘의 [2단계 과정( 물체와의 교차점 계산 )](#ray-tracing-algorithm)에서 여러 가지 `Object와 Ray의 교차점을 계산할 때 사용`한다<br>

<br>

## Ray-Tracing에 사용하는 3가지 경우

### 1. Object와 Ray의 충돌 검출
특정 pixel에 대응하는 Ray가 Scene의 Object와 교차하는지 알아보려면, 그 Object와 Ray의 교차점을 계산해야 한다<br>

### 2. Ray 굴절 및 반사 계산
Ray와 Object가 교차할 때, 이 교차점을 기준으로 Ray의 방향이 굴절 또는 반사될 수 있다<br>
이 경우 새로운 Ray에 따라 Line-Sphere Intersection 반복적으로 계산한다<br>

### 3. Shadow 계산
Lighting이 있을 때, Object에 Shadow가 생긴다<br>
Lighting에서 발사된 Ray가 object와 교차하는지 판단하여 그림자를 결정한다<br>

<br>
<br>

# Ray Tracing을 구현하기 위해 필요한 정보

### 1. Ray( 광선 정보 )

### 2. Hit( 충돌 정보 )
normal vector란 Ray에 충돌한 위치에서 표면의 수직 벡터를 의미한다<br>
Graphics에서 normal vector는 unit vector로 저장한다<br>

### 3. Ray Tracer( rendering에 필요한 정보 )