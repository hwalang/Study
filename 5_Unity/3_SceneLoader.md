
- [Scene Loader class를 만드는 이유](#scene-loader-class를-만드는-이유)
    - [Scene 전환 작업 예시](#scene-전환-작업-예시)
- [예시](#예시)

<br>

# Scene Loader class를 만드는 이유
Unity에서 제공하는 SceneManager API를 사용해서 Scene을 변경할 수 있지만, SceneLoader class를 만드는 이유가 있다.<br>

1. `Scene 전환 시 초기화 작업`, User Input의 제어, 데이터 작업 등 많은 작업이 필요하기 때문이다.<br>
2. Scene 전환 시 `1 frame에 Scene이 완벽하게 Loading되지 않는다`. object가 loading되는 장면을 User에게 노출하지 않기 위함이다.<br>
3. 위 작업이 준비될 때까지 Art나 Animation 등 다양한 방법으로 `Loading 화면을 구성`하기 위함이다.<br>

<br>
<br>

### Scene 전환 작업 예시

timeScale, User Input, Data


<br>
<br>

# 예시
```c#
public enum SceneType
{
  Title,
  Lobby,
  InGame,
}

public class SceneLoader : SingletonBehaviour<SceneLoader>
{
  public void LoadScene(SceneType sceneType)
  {
    Logger.Log($"{sceneType} scene loading...");

    Time.timeScale = 1f;
    SceneManager.LoadScene(sceneType.ToString());
  }

  // 현재 Scene을 reloading 하는 기능
  public void ReloadScene()
  {
    Logger.Log($"{SceneManager.GetActiveScene().name} scene loading...");

    Time.timeScale = 1f;
    SceneManager.LoadScene(SceneManager.GetActiveScene().name);
  }
}
```
timeScale을 세팅한다. 이 또한 Scene 전환 시 필요한 작업 중 하나다.<br>
일시정지 시 timeScale이 0, 게임 기획 상 timeScale이 0 ~ 1 사이 또는 1보다 큰 경우가 있다.<br>
`Scene을 Loading 했을 때 timeScale을 다시 1로 초기화 하는 작업`이다.<br>