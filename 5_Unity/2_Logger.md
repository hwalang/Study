# Logger Class

1. 추가적인 정보 표현 : 대표적으로 `Time Stamp는 판단의 근거`
   - 게임 진행에서 각 단계가 얼마나 걸리는지 측정 가능
   - 어느 부분을 최적화 해야 하는지
   - 최적화로 성능이 얼마나 좋아졌는지
   - 원인을 알 수 없는 버그가 발생했을 때, 버그가 발생한 시간대의 로그를 분석하여 원인의 실마리를 찾을 수 있음
2. 출시용 빌드를 위한 로그 제거
   - 출시용 게임에 로그를 남기면 성능에 큰 부하가 생기기 때문에 에러용 로그만 남긴다.
   - 일반, warning 로그는 제거한다.
   - 일일이 주석처리하는 것보다 일괄적으로 관리하기 위한 Log class를 만든다.

</br>
</br>

```c#
using System.Diagnostics;   // Conditional

public static class Logger
{
  [Conditional("DEV_VER")]
  public static void Log(string msg)
  {
    UnityEngine.Debug.LogFormat("[{0}] {1}", System.DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"), msg);
  }

  [Conditional("DEV_VER")]
  public static void LogWarning(string msg)
  {
    UnityEngine.Debug.LogWarningFormat("[{0}] {1}", System.DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"), msg);
  }

  public static void LogError(string msg)
  {
    UnityEngine.Debug.LogErrorFormat("[{0}] {1}", System.DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"), msg);
  }
}
```
일반, warning, error 수준의 log 함수를 생성한다.</br>

Conditional은 조건부 컴파일 symbol이다.</br>

ProjectSettings - Player - Script Compilation - Scripting Define Symbols </br>
SDS는 project 전반에서 정의하여 사용할 수 있는 symbol이다.</br>
SDS List에 Conditional 속성에서 명시한 symbol( DEV_VER )이 있으면 Log와 LogWarning이 실행되고,아니면 무시된다.</br>
따라서 개발 단계에서 Log와 LogWarning이 실행되도록 SDS List에 DEV_VER을 추가한다.</br>

LogError는 개발용, 출시용에 상관 없이 사용하기 때문에 Conditional 속성을 부여하지 않았다.</br>
