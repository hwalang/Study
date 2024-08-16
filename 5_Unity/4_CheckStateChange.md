# 개발 편의성

Editor에서 게임 오브젝트의 상태를 runtime에 확인할 수 있다<br>

<br>
<br>

# 예시 1 : PlayerStateView
[Game Programming Pattern Repository](https://github.com/hwalang/Game-Programming-Pattern-For-Unity.git)<br>
Play -> Design Pattern -> State 참고<br>

```c#
// A user interface that responds to internal state changes
[RequireComponent](typeof(PlayerController))
public class PlayerStateView : MonoBehaviour
{
  [SerializeField] private Text m_LabelText;

  private PlayerController m_Player;
  private SimplePlayerStateMachine m_PlayerStateMachine;

  // mesh to change color
  private MeshRenderer m_MeshRenderer;

  private void Awake()
  {
    m_Player = GetComponent<PlayerController>();
    m_MeshRenderer = GetComponent<MeshRenderer>();

    // cache to save typing
    m_PlayerStateMachine = m_Player.PlayerStateMachine;

    // listen for any state changes
    m_PlayerStateMachine.stateChanged += OnStateChanged;
  }

  void OnDestroy()
  {
    // unregister the subscription if we destroy the object
    m_PlayerStateMachine.stateChanged -= OnStateChanged;
  }

  // change the UI.Text when the state changes
  private void OnStateChanged(IState state)
  {
    if (m_LabelText != null)
    {
      m_LabelText.text = state.GetType().Name;
      m_LabelText.color = state.MeshColor;
    }
    ChangeMeshColor(state);
  }

  // set mesh material to the current state's associated color
  private void ChangeMeshColor(IState state)
  {
    if (m_MeshRenderer == null) return;

    // meshRenderer.sharedMaterial.color = state.MeshColor;
    m_MeshRenderer.material.SetColor("_BaseColor", state.MeshColor);
  }
}
```
Player Object는 PlayerStateView를 Component로 가진다.<br>


```c#
public interface IColorable
{
  public Color MeshColor { get; set; }
}

public interface IState : IColorable
{
  public void Enter() {}
  public void Execute() {}
  public void Exit() {}
}
```
UI.Text의 색깔을 바꾸기 위한 IColorable interface를 IState가 가진다.<br>

```c#
public class IdleState : IState
{
  ...
  // color to change player ( alternately : pass in color value with constructor )
  Color meshColor = Color.white;
  public Color MeshColor { get => meshColor; set => meshColor = value; }
}
```
각 State class에 맞는 색깔을 지정한다.<br>