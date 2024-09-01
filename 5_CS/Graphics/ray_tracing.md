- [Introduce](#introduce)
  - [3D 장면을 2D 화면에 rendering 하는 2가지 방법](#3d-장면을-2d-화면에-rendering-하는-2가지-방법)
    - [1. object-order rendering](#1-object-order-rendering)
    - [2. image-order rendering](#2-image-order-rendering)
    - [3. 차이점](#3-차이점)
- [Ray Tracing Algorithm](#ray-tracing-algorithm)
  - [Projection](#projection)
  - [Ray-Sphere Intersection](#ray-sphere-intersection)
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

![alt text](Images/Ray_Tracing.png)<br>
Scene Object를 Screen에 비추기 위해서 어떻게 할까?<br>

<br>

1. Camera가 바라보는 방향으로 `모든 pixel에서 Scene으로 pixel 1개당 하나의 Ray를 쏜다`<br>
   - 나중에는 각 pixel에서 여러 개의 Ray를 Scene으로 쏘는 경우도 있다.
2. `Ray가 처음으로 충돌한( hit ) 지점( point )의 색깔( pixel )을 계산`한다.
3. `계산 값을 Screen의 pixel에 적용`한다.

<br>

`Ray의 방향`은 DirectX에서는 `+Z방향( Left-handed Systems )`이다.<br>

가상의 눈에서 가상 화면의 각 pixel을 통과하는 경로를 추적하고, 이를 통해 보이는 object의 색상을 계산하는 방식이다<br>
먼저 빛이 screen을 통과하면 가장 가까운 object를 식별한다.<br>
object를 식별하면 ray tracing 알고리즘을 통해 screen에 보일 pixel 값을 정한다.<br>
pixel 값은 object의 재질, 광원을 결합하여 최종 pixel( 색상 ) 값을 결정한다<br>

<br>

## Projection
Orthographic Projection( 정투영 )과 Perspective Projection( 원근투영 )이 있다<br>
Ray를 Screen에 수직인 방향( vec3(0, 0, 1) )으로 쏴주는 것을 Orthographic projection이라 한다<br>

<br>

## Ray-Sphere Intersection
[ wiki - Line-Sphere Intersection ](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection)<br>
![<alt text>](Images/ray_sphere_intersection.png)<br>

<br>

## Ray Tracing을 구현하기 위해 필요한 정보

### 1. Ray( 광선 정보 )

### 2. Hit( 충돌 정보 )
normal vector란 Ray에 충돌한 위치에서 표면의 수직 벡터를 의미한다<br>
Graphics에서 normal vector는 unit vector로 저장한다<br>

### 3. Ray Tracer( rendering에 필요한 정보 )