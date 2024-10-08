# DirectX11 환경설정
### Tool
- visual studio
- vcpkg( IMGUI, glm )

<br>

## 1. vcpkg 설치
1. [vcpkg github](https://github.com/microsoft/vcpkg) 해당 링크에 들어가서 README.md의 Getting Started로 이동
2. Quick Start: Windows 따라한다.
3. clone을 받으면 vcpkg가 설치되고, `cd vcpkg( vcpkg 경로 )를 통해 접근`할 수 있다.
4. dir 명령어를 통해 vcpkg 내부의 파일을 볼 수 있으며, bootstrap-vcpkg.bat를 복붙( enter, ctrl + v )해서 다운로드를 진행한다.
5. image 처리를 위해서 "vcpkg install stb:x64-windows" 명령어로 stb를 설치한다.
6. 수학 연산을 위한 GLM 세팅

vcpkg 설치 끝

<br>

## 2. library 설치( IMGUI )
[imgui github](https://github.com/ocornut/imgui.git)에서 수동으로 설치해도 된다. 하지만 많이 번거롭기 때문에 vcpkg를 이용해서 설치한다.
1. vcpkg 경로에서 "vcpkg search imgui" 명령어를 이용해서 vcpkg에 imgui가 있는지 확인한다.
2. win32로 window를 띄우고 directX11을 사용하기 때문에 "imgui[win32-binding]"와 "imgui[dx11-binding]"를 다운한다.
   - vcpkg install imgui[win32-binding,dx11-binding]:x64-windows
3. 같은 경로에서 "vcpkg integrate install"를 통해 visual studio에서 vcpkg를 사용할 수 있게 세팅한다.

### 2.1. GLM
vcpkg 경로에서 `vcpkg install glm:x64-windows` 입력 후 설치를 진행한다<br>


<br>

## 3. visual studio 2022 세팅
- `멀티쓰레드 이용을 위한 open MP 사용`<br>
   ![openMP 사용](Images/Settings/openMP.png)<br>
  - 프로젝트의 properties로 이동
  - C/C++ -> All Options -> open 검색
  - Configuration을 Release로 변경
  - Open MP Support를 YES로 세팅