---
description: UI 이미지 생성 후 Unreal Editor로 자동 임포트
---

# UI 에셋 임포트 워크플로우

## 1. 이미지 생성
- `generate_image` 도구로 UI용 이미지 생성
- 생성된 이미지를 `UMGDemo-Images/` 하위에 복사
- 경로는 `UMGDemo/Content/`와 동일 구조 유지
  - 예: `UMGDemo-Images/UI/Textures/T_PatternName.png`

## 2. 이미지 복사
```powershell
Copy-Item "생성된이미지경로" -Destination "d:\github\ue5antig-umg\UMGDemo-Images\UI\Textures\파일명.png"
```

## 3. Remote Execution으로 임포트
// turbo
```powershell
cd d:\github\ue5antig-umg
python Scripts\RemoteExecute.py
```

## 사전 조건
- Unreal Editor 실행 중
- `Edit → Editor Preferences → Python → Enable Remote Execution` 활성화
