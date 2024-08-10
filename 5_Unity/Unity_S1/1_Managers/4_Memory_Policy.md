# Memory Policy

## 1. 필요할 때마다 memory로 가져와서 사용
게임을 진행하면서 끊김 현상이 발생할 수 있다.</br>

</br></br></br>

## 2. 모든 Resource를 memory에 올려놓고 사용
첫 로딩 화면에서 Resource를 모두 가져온다.</br>
일반적으로 해당 방법을 사용한다.</br>

</br></br></br>

## 3. 참고 코드 - 코드 분석이 필요하다. c# 문법 포함
``` c#
// Object를 명확히 정의한다. System.Object가 있기 때문이다.
using Object = UnityEngine.Object;


public class ResourceManager
{
    // 가져온 resource를 메모리에 올려둔다.
    private Dictionary<string, UnityEngine.Object> _resources = new Dictionary<string, UnityEngine.Object>();
    private Dictionary<string, AsyncOperationHandle> _handles = new Dictionary<string, AsyncOperationHandle>();


    // 메모리에 있는 Resource를 필요할 때 꺼내 사용하는 방법을 제공
    #region Load Resource
    // _resources에 존재하는 데이터를 가져온다.
    public T Load<T>(string key) where T : Object
    {
        if (_resources.TryGetValue(key, out Object resource)) return resource as T;
        return null;
    }

    // _resource에 존재하는 prefab을 가져온다.
    public GameObject Instantiate(string key, Transform parent = null, bool pooling = false)
    {
        GameObject prefab = Load<GameObject>(key);
        if (prefab == null)
        {
            Debug.LogError($"Failed to load prefab : {key}");
            return null;
        }

        //if (pooling) return Managers.Pool.Pop(prefab);

        GameObject go = Object.Instantiate(prefab, parent);
        go.name = prefab.name;

        return go;
    }

    public void Destory(GameObject go)
    {
        if (go == null)
            return;

        //if (Managers.Pool.Push(go))
        //    return;

        Object.Destroy(go);
    }
    #endregion


    // 모든 Resource를 메모리에 올려둔다.
    #region Addressable
    /*
    Async는 비동기 함수다.
    동기 함수는 해당 함수의 작업이 끝날 때까지 게임이 멈춘다. 하지만 비동기 함수는 작업이 진행될 때 다른 작업도 할 수 있다.
    LoadAsync 함수는 작업이 끝나면 callback 함수를 OS에 전달해서 작업이 완료됐음을 알려준다.
     */
    private void LoadAsync<T>(string key, Action<T> callback = null) where T : UnityEngine.Object
    {
        // Cache
        if (_resources.TryGetValue(key, out Object resource))
        {
            callback?.Invoke(resource as T);
            return;
        }

        string loadKey = key;
        if (key.Contains(".sprite"))
            loadKey = $"{key}[{key.Replace(".sprite", "")}]";

        var asyncOperation = Addressables.LoadAssetAsync<T>(loadKey);
        // 위 비동기 작업이 완료되면 수행하는 함수를 작성
        asyncOperation.Completed += (op) =>
        {
            _resources.Add(key, op.Result);         // _resources에 가져온 데이터를 저장한다.
            _handles.Add(key, asyncOperation);
            callback?.Invoke(op.Result);
        };
    }

    // Addressable Group에서 세팅한 label을 가져온다.
    public void LoadAllAsync<T>(string label, Action<string, int, int> callback) where T : UnityEngine.Object
    {
        var opHandle = Addressables.LoadResourceLocationsAsync(label, typeof(T));   // label에 해당하는 모든 resource path 목록을 가져온다.

        // 목록에서 Resource를 하나씩 loading한다.
        opHandle.Completed += (op) =>
        {
            int loadCount = 0;                      // 몇 개의 resource를 가져왔나
            int totalCount = op.Result.Count;       // 총 몇 개의 resource가 존재하나

            foreach (var result in op.Result)
            {
                // Group에서 sprite 파일을 알려주는 key 없이 가져오는 경우에는 text 파일로 인식하는 경우가 존재한다.
                // 이를 대비해서 sprite 파일에는 무조건 이름에 .sprite를 붙여서 sprite임을 인식시킨다.
                if (result.PrimaryKey.Contains(".sprite"))
                {
                    LoadAsync<Sprite>(result.PrimaryKey, (obj) =>
                    {
                        loadCount++;
                        callback?.Invoke(result.PrimaryKey, loadCount, totalCount); // 하나의 resource를 받아올 때마다 callback 함수를 보낸다.
                    });
                }
                else
                {
                    LoadAsync<T>(result.PrimaryKey, (obj) =>
                    {
                        loadCount++;
                        callback?.Invoke(result.PrimaryKey, loadCount, totalCount);
                    });
                }
            }
        };
    }

    // 게임 도중에 메모리에 존재하는 resource를 날려야 하는 일이 생기면 사용한다.
    public void Clear()
    {
        _resources.Clear();

        foreach (var handle in _handles)
            Addressables.Release(handle);

        _handles.Clear();
    }
    #endregion
}
```