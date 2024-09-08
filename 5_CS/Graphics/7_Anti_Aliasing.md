- [Anti-Aliasing](#anti-aliasing)
- [Super Sampling Anti Aliasing( SSAA )](#super-sampling-anti-aliasing-ssaa-)

<br>

# Anti-Aliasing
`화면에 rendering될 때 발생하는 계단 현상( Jagged Edges )을 줄여 시각적 품질을 향상시키는 방법`이다<br>

<br><br>

# Super Sampling Anti Aliasing( SSAA )
[ widi - Supersampling ](https://en.wikipedia.org/wiki/Supersampling)<br>
Anti-Aliasing 기술 중 하나로, `jagged edges를 없애는 과정`이다<br.>

ray-tracing에서 하나의 pixel에서 하나의 ray를 발사했다<br>
`super sampling은 하나의 pixel에서 여러 개의 ray를 발사`한다<br>
여러 개의 ray를 쏘기 때문에 더 부드러운 이미지를 얻을 수 있지만, `여러 개의 ray에 대한 연산이 필요하기 때문에 성능 저하`가 발생한다.<br>
때문에 blur 효과를 이용하기도 한다<br>