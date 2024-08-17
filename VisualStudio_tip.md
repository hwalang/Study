**Visual Studio 2022 TIP**
- [Properties](#properties) : project 또는 solution 속성
  - [1. cpp compiler](#1-cpp-compiler)
  - [2. Preprocessor Definitions](#2-preprocessor-definitions)
- [Functions](#functions) : visual studio 기능
  - [1. Check Thread](#1-check-thread)
  - [2. Open Containing Folder](#2-open-containing-folder)
  - [3. 하나의 solution에 있는 projects를 한 번에 실행](#3-하나의-solution에-있는-projects를-한-번에-실행)
- [Shortcut Keys](#shortcut-keys) : 단축키
  - [alt + f12 ( peek definition )](#alt--f12--peek-definition-)

<br>

## Properties
### 1. cpp compiler
![change compiler](VisualStudio_Images/determine_compiler.png)

어떤 cpp compiler를 사용할지 결정한다.

<br>

### 2. Preprocessor Definitions
![edit preprocessor](VisualStudio_Images/preprocessor.png)

scanf, sprintf를 사용할 때 발생하는 warning을 없애줄 때 유용하다.

<br>
<br>

## Functions
### 1. Check Thread
![alt text](VisualStudio_Images/Check_Thread.png)<br>
Multi-Thread 환경에서 `현재 수행 중인 Thread를 알고 싶다면`, 프로그램을 일시정지 한 뒤에 Thread 목록을 살펴보면 된다.<br>

<br>

### 2. Open Containing Folder
![open containing folder](VisualStudio_Images/open_containing_folder.png)

선택한 파일이 위치한 Folder를 연다.

<br>

### 3. 하나의 solution에 있는 projects를 동시에 실행
Solution - Properties - Common Properties - Startup Project - check `Multiple startup projects`<br>

![alt text](/6_CS/GameServer/Images/Set_Multiple_projects.png)!

2개 이상의 projects를 동시에 실행해서 테스트 할 수 있다.<br>
Action 값을 Start로 세팅한 projects만 실행된다.<br>

<br>
<br>

## Shortcut Keys
### alt + f12 ( peek definition )
![예시 이미지](VisualStudio_Images/peek_definition.png)
  - peek definition
  - 선택한 코드의 정의를 파일 이동 없이 보여준다.
