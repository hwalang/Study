- [Lambertian Reflection](#lambertian-reflection)
  - [1. Diffuse Surface](#1-diffuse-surface)
  - [2. Diffuse Reflection과 Specular Reflection](#2-diffuse-reflection과-specular-reflection)
  - [3. Lambert's Cosine Law](#3-lamberts-cosine-law)
  - [4. Diffuse Lighting Model](#4-diffuse-lighting-model)
- [Phong Reflection Model](#phong-reflection-model)
  - [1. Diffuse Reflection](#1-diffuse-reflection)
  - [2. Specular Reflection](#2-specular-reflection)
  - [3. Ambient Reflection](#3-ambient-reflection)
  - [4. Phong Reflection Model 수식](#4-phong-reflection-model-수식)

<br>

조명이 빛을 반사해서 우리 눈에 Object가 어떻게 보이는 지에 대한 모델을 알아본다<br>

# Lambertian Reflection
Lambertian Reflection은 종종 diffuse reflection을 위한 model로 사용한다<br>

## 1. Diffuse Surface
light vector가 모든 방향으로 같은 양의 빛을 반사한다<br>
때문에 `어느 방향에서 봐도 똑같은 밝기로 보이는 표면`이다<br>

## 2. Diffuse Reflection과 Specular Reflection
Diffuse Surface에서 나타나는 2가지 reflection을 살펴본다<br>

[ Diffuse reflection - wiki ](https://en.wikipedia.org/wiki/Diffuse_reflection)<br>

Diffuse Reflection이란, `빛, 파동, 입자가 반사되어 표면에 입사한 광선이 specular reflection( 정반사 )처럼 한 각도가 아니라 여러 각도로 scatter 되는 것`을 의미한다<br>
여기서 specular reflection은 거울 반사가 대표적인 예시이다<br>

![alt text](Images/PhongModel/diffuse_surface.png)<br>

위 그림은 매끄러운 또는 광택이 있는 표면에서 diffuse reflection과 specular reflection이다<br>
그림의 ray는 luminous intensity를 나타내며, 이러한 intensity는 Lambert's consine law에 의해 달라진다<br>

## 3. Lambert's Cosine Law
[ Lambert's cosine law ](https://en.wikipedia.org/wiki/Lambert%27s_cosine_law)<br>
[ Lambertian Reflection - wiki ](https://en.wikipedia.org/wiki/Lambertian_reflectance)<br>

`Diffuse Reflection에 대한 법칙`이다<br>
Lambert's cosine law을 따르는 surface를 lambertian surface라 하며, 위 Diffuse Surface가 이에 해당한다<Br>

![alt text](Images/PhongModel/lambertian_reflection.png)<br>

Diffuse surface로 들어오는 incident light( 입사광 )

Lambertian Surface( Diffuse Surface )에서 반사된 빛의 강도( intensity )는 $I = I_\circ \dot \cos \theta$로 계산한다<br>
- $I$: reflction light intensity
- $I_\circ$: incident light
- $\theta$: incident light와 surface의 normal vector 사이의 각도

즉, `surface가 빛을 받았을 때, 그 surface에서 reflected light intensity가 incident light의 방향과 surface's normal vector가 이루는 각도의 cosine 값에 비례`한다<br>
해가 뜨는 위치에 따른 빛의 세기를 생각하면 편하다<br>

incident light가 surface에 수직($\theta = 0^\circ$)으로 입사할 때, reflected light intensity가 가장 크며, incident light가 surface에 비스듬히 입사할수록( $\theta$가 커질수록 ) reflected light intensity가 줄어든다<br>

## 4. Diffuse Lighting Model
Graphics에서 Lambert's cosine law를 사용하는 조명 모델이다<br>
이를 통해 물체의 표면이 특정 조명에서 어느 방향으로든 고르게 빛을 반사하는 것을 시뮬레이션 할 수 있다<br>


<br><br>


# Phong Reflection Model
[ Phong Reflection Model - wiki ](https://en.wikipedia.org/wiki/Phong_reflection_model)<br>

`Graphics에서 물체의 표면이 어떻게 빛을 반사하는지를 시뮬레이션하는 조명 모델 중 하나`이다<br>

HW의 한계로 인해 저렴한 비용으로 높은 성능을 추구했던 과거에 많이 사용했다<br>
현실의 물리 법칙을 많이 무시하기 때문에 지금은 잘 사용하지 않는다<br>
하지만 현대의 reflection model은 phong reflection model 구조에서 확장하는 방식이 많기 때문에 알아두는 것이 좋다.<br>

![alt text](Images/PhongModel/phong_reflection_model.png)<br>

해당 Model은 object의 surface에서 reflection 되는 빛을 세 가지 요소로 나눈다<br>
`Diffuse( 난반사 ) Reflection, Specular( 정반사 ) Reflection, Ambient Lighting( 주변광 ) Reflection을 함께 고려`해서 현실적인 조명으로 표현하려고 한다<br>

<br>

## 1. Diffuse Reflection
[ Lambert's cosine law ](#3-lamberts-cosine-law)에 따라 `surface에 닿는 빛이 모든 방향으로 고르게 반사되는 현상`이다<br>

$I_d = k_d \dot I_{light} \dot (L \dot N)$<br>

- $I_d$: diffuse reflection intensity
- $k_d$: surface의 diffuse reflection 계수( 얼마나 diffuse를 반사하나? )
- $I_{light}$: light intensity
- $L$: light의 방향 벡터
- $N$: surface normal vector
- $L \dot N$: light direction과 normal vector 사이의 cosine 값( incident light 각도 )

<br>

## 2. Specular Reflection
`매끄러운 표면에서 빛이 한 방향으로 강하게 반사되는 현상`이다<br>
이러한 현상은 반짝거리는 효과를 만들 때 사용한다<br>
`surface를 바라보는 눈이 어디 있는지도 영향`을 미친다<br>

$I_s = k_s \dot I_{light} \dot (R \dot V)^n$

- $I_s$: specular reflection intensity
- $k_s$: surface specular reflection 계수
- $R$: 반사 벡터
- $V$: viewer의 방향 벡터
- $n$: 표면의 반짝임을 나타내는 지수( n이 클수록 빛의 반사가 더 좁고 날카롭다 )

<br>

## 3. Ambient Reflection
빛이 없어도 보이는 빛이며, object 자체의 빛이라고 생각하면 된다<br>
정확히 말하면, `물체가 어두운 환경에서 빛을 완전히 흡수하지 않고 약간의 빛을 반사하는 현상`이다<br>

$I_a = k_a \dot I_{ambient}$<br>

- $I_a$: ambient lighting reflection intensity
- $k_a$: surface의 ambient reflection 계수( 얼마나 주변광을 반사하나? )
- $I_{ambient}$: 환경에서의 ambient intensity

<br>

## 4. Phong Reflection Model 수식
$$I = I_d + I_s + I_a$$

$I$는 `물체 표면에서 반사되는 최종 조명의 강도`이다<br>