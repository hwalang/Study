# Handle

어떤 `resource나 object에 대한 참조 혹은 식별자`다.</br>
특정 resource를 직접 다루는 대신 `handle을 통해 상호작용`한다.</br>

## 예시 1 : AysncOperationHandle from Unity
[AsyncOperationHandle](/5_Unity/Unity_S1/1_Managers/4_Memory_Policy.md) </br>
```c#
public class ResourceManager
{
  private Dictionary<string, AsyncOperationHandle> _handles = new Dictionary<string, AsyncOperationHandle>();

  private void LoadAsync<T>(string key, Action<T> callback = null) where T : UnityEngine.Object
  {
    string loadKey = key;
    if (key.Contains(".sprite"))
      loadKey = $"{key}[{key.Replace(".sprite")}]";
    
    var asyncOperation = Addressables.LoadAssetAsync<T>(loadKey);
    aysncOperation.Completed += (op) =>
    {
      _handles.Add(key, aysncOperation);
      callback?.Invoke(op.Result);
    }
  }

  public void Clear()
  {
    foreach (var handle in _handles)
      Addressables.Release(handle);
    
    _handles.Clear();
  }
}
```
`_handles는 Addressable 시스템을 통해 비동기적으로 load 된 resource에 대한 handle을 저장`한다.</br>
_handles는 AsyncOperationHandle 객체를 저장하는 Dictionary 객체이다. `각각의 resource를 load 할 때 생성되는 handle을 key 값과 함께 보관`한다.</br>

1. `resource 해제`
   - Unity의 Addressables 시스템은 resource를 비동기적으로 load하고 관리한다. 이때 `resource를 해제하기 위해서는 load 작업과 관련된 AsyncOperationHandle이 필요`하다.
   - _handles Dictionary에 handle을 저장하면, 필요할 때 `특정 resource를 해제( Release )`할 수 있다. 이 과정에서 `handle을 이용하여 Addressables 시스템에 resource 해제 요청`을 한다.
2. `resource 관리`
   - `handle을 저장`해서 어떤 resource가 load 됐는지, 그 resource를 어떻게 관리할 것인지에 대한 `정보를 추적`할 수 있다.
   - Clear() 메소드를 통해 _handles에 저장된 모든 handle에 대해 Addressable.Release();를 호출하여, 현재 memory에 load 된 resource를 해제할 수 있다.
   - `memory leak를 방지`하고, `게임 memory 사용량을 효율적으로 관리`한다.
