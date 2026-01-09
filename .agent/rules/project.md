---
trigger: always_on
---

# 프로젝트 규칙

이 문서는 UMGDemo 프로젝트에서 작업할 때 항상 적용되는 규칙들을 정의합니다.

## 언어 사용 규칙

### 1. 대답 언어
- **모든 AI 응답은 한국어로 작성**
- 설명, 가이드, 대화 등 모든 텍스트는 한국어 사용

### 2. 마크다운 파일
- **모든 마크다운 파일 내용은 한국어로 작성**
- 적용 대상:
  - `task.md`
  - `implementation_plan.md`
  - `walkthrough.md`
  - 기타 모든 `.md` 문서

### 3. 소스코드 주석
- **모든 소스코드 주석은 영어로 작성**
- 적용 대상:
  - C++ 파일 (`.h`, `.cpp`)
  - Blueprint 스크립트
  - 기타 모든 프로그래밍 언어 파일

## 프로젝트 구조

### 메인 프로젝트
- **UMGDemo 서브 디렉토리**: UE5.7 프로젝트
- 별도 언급이 없으면 UMGDemo가 기본 작업 대상
- 프로젝트 경로: `.\UMGDemo`

## 엔진 버전
- **Unreal Engine 5.7.1**

## 빌드 규칙
- **빌드는 항상 사용자가 직접 수행**
- AI가 자동으로 빌드 명령어(`Build.bat`, `UnrealBuildTool` 등)를 실행하지 않음
- 사용자가 Visual Studio나 Unreal Editor에서 직접 빌드
- 엔진 경로: `E:\WorkTemp\Epic Games\UE_5.7`

## C++ 코딩 규칙 (Unreal Engine)

### 헤더 파일 include 순서
- **`.generated.h` 파일은 반드시 마지막 `#include`여야 함**
- 올바른 순서:
  1. `#include "CoreMinimal.h"` (첫 번째)
  2. 기타 Engine/Module 헤더들
  3. 동일 모듈 내 헤더들
  4. `#include "ClassName.generated.h"` (마지막)

```cpp
// 올바른 예시
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryTypes.h"
#include "InventoryComponent.generated.h"  // 반드시 마지막!
```

> [!IMPORTANT]
> **AI가 헤더 파일(`.h`)을 수정한 경우, 반드시 HeaderReorder 도구를 실행해야 합니다:**
> 
> ```powershell
> cd .\Tools\HeaderReorder; dotnet run -- ".\UMGDemo" --all
> ```
> 
> 이 도구는 자동으로 `.generated.h`가 마지막 include가 되도록 재정렬합니다.

> [!TIP]
> **수동 실행이 필요한 경우 (헤더 순서 에러 발생 시):**
> 
> ```powershell
> cd .\Tools\HeaderReorder
> dotnet run -- ".\UMGDemo" --all
> ```

---

> [!IMPORTANT]
> 이 규칙들은 모든 작업에 자동으로 적용되며, 새로운 채팅 세션에서도 이 파일을 참조하여 일관성을 유지합니다.
