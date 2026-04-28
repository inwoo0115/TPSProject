# TPSProject

Unreal Engine 5.4 기반 멀티플레이 3인칭 슈터(TPS) 프로젝트.
플레이어 캐릭터, 보스 AI, 커스텀 능력 시스템, 그래플링, 인벤토리, 온라인 멀티플레이를 포함한 통합 게임플레이 프로토타입입니다.

- **엔진**: Unreal Engine 5.4
- **언어**: C++ / Blueprint
- **개발 기간**: 2025.05.25 ~ 2025.06.23
- **장르**: Third-Person Shooter (Co-op / Multiplayer)

---

## 주요 기능 (Features)

### 캐릭터 & 입력
- `ATPSCharacterBase` 계층 구조 (`Player`, `Boss`, `NonCharacterBase`)로 플레이어/보스/일반 NPC 분리
- **Enhanced Input System** 기반 입력 (Move / Look / Jump / Run / Attack / Aim / Reload / SpAction / SpAttack / Ultimate / Drone / Interact)
- Aim 시 카메라 줌 Timeline, Controller 회전 리플리케이션

### 커스텀 능력 시스템 (Custom Ability System)
GAS를 사용하지 않고 `UTPSEquipmentAbilityBase`를 기반으로 직접 구현한 능력 프레임워크.
- **무기(Weapon)**, **드론(Drone)**, **스페셜 어택(SpAttack, 그레네이드 등)**, **궁극기(Ultimate)** 4종 슬롯
- `EAbilityType` 분류 + 능력별 Context 구조체(`FWeaponContext`, `FDroneSkillContext`, `FSpAttackSkillContext`, `FUltimateSkillContext`)
- `ApplyAbility / InitializeAbilityEvent / CancelAbility` 라이프사이클
- 네트워크 리플리케이션 지원 (`IsSupportedForNetworking`)

### 무기
- 데이터 기반 무기 정의 (`UTPSWeaponData` DataAsset)
- 구현된 무기: `ATPSBasicRifle`, `ATPSFlameRifle`
- `UTPSWeaponComponent` 로 장착/교체 관리, `ServerRPCEquipWeapon` 으로 동기화

### AI
- BehaviorTree + Blackboard (`ATPSAIController`)
- **BTService**: `CheckDistance`, `CheckInRange`, `Detect`
- **BTTask**: `Attack`, `CastSkill`, `CastUlti`, `Jump`, `TurnToTarget`
- `UEnvQueryContext_TargetActor` 환경 쿼리로 타겟팅
- 보스 전용 스킬/궁극기 시전 로직

### 멀티플레이
- `OnlineSubsystem` / `OnlineSubsystemUtils` 통합 (로비·세션 관리)
- Server / Multicast / Client RPC 패턴 전반 적용 (공격, 스킬, 궁극기, 인벤토리, AI 동기화)
- Replicated 프로퍼티: `IsRun`, `CurrentControllerRotation`, `SpInteractionTargetActor` 등
- `ATPSMultiPlayerController` + `ClientUpdateTarget` RPC

### 인벤토리 & 상호작용
- `UTPSAbilityItem` (이름·설명·아이콘·`EAbilityType`) 기반 아이템 데이터
- 월드 상호작용: `ATPSArmoryInteractionObject`, `ATPSInventoryInteractionObject`, `ATPSRopeActionInteractionObject`, `ATPSOnlineInteractionObject`
- `ServerInitializeAbilityList` 로 능력 리스트 서버 초기화

### 그래플링 / 특수 액션
- `UTPSRopeActionComponent` — `CableComponent` 기반 로프/그래플링
- 속도·가속도 추적, `SetIsGrappling`, `SetRopeLocation`

### UI (UMG 18+ 위젯)
- HUD: `UTPSHUDWidget`
- 메뉴: `UTPSMenuWidget`, `UTPSPauseWidget`, `UTPSOnlineMenuWidget`
- 인벤토리: `UTPSInventoryWidget`, `UTPSInventoryItemWidget`
- 장비 설정: `UTPSEquipmentWidget`, `UTPSMainWeaponSettingWidget`, `UTPSDroneSettingWidget`, `UTPSSpAttackSettingWidget`, `UTPSUltimateSettingWidget`
- 정보: `UTPSEquipmentInfoWidget`, `UTPSItemInfoWidget`

### 부가 시스템
- **PoolManager** — 발사체/이펙트 오브젝트 풀링
- **GameInstance** — `UTPSGameInstance`, `UTPSOnlineSubsystem`, `UTPSGameplayEventSubsystem`, `UTPSSaveGame`
- **GameMode** — `Main`, `Lobby`, `Menu` 분리

---

## 프로젝트 구조

```
Source/TPSProject/
├── AI/                        # AIController, BTService, BTTask, EnvQuery
├── Animation/                 # AnimInstance, AnimNotify
├── Character/                 # CharacterBase / Player / Boss / NonCharacter
├── CharacterComponent/        # Weapon, Skill, Ultimate, Drone, RopeAction 등
├── CharacterEquipment/        # 무기·드론·스페셜·궁극기 장비 액터
├── CharacterEquipmentAbility/ # 능력 구현체 (Weapon/Drone/SpAttack/Ultimate)
├── GameInstance/              # GameInstance, OnlineSubsystem, SaveGame
├── GameMode/                  # Main, Lobby, Menu GameMode
├── Interaction/               # 월드 상호작용 오브젝트
├── Interface/                 # EventComponent, Interactable, SetTarget, UltiGauge
├── Item/                      # AbilityItem 데이터
├── Player/                    # PlayerController
├── PoolManager/               # 오브젝트 풀
├── Projectile/                # Bullet, Grenade, HommingMissile
├── Summons/                   # Drone, Ultimate, SkillRangeDecal
└── Widget/                    # UMG 위젯 (HUD/Inventory/Equipment/Menu)
```

---

## 기술 스택

| 분류 | 사용 기술 |
| --- | --- |
| 엔진 | Unreal Engine 5.4 |
| 언어 | C++17 (UE), Blueprint |
| 입력 | Enhanced Input |
| AI | AIModule, BehaviorTree, EQS |
| 네트워크 | OnlineSubsystem, RPC, Replication |
| UI | UMG |
| VFX/기타 | Niagara, CableComponent |
| 플러그인 | ModelingToolsEditorMode, VisualStudioTools |

---

## 빌드 & 실행

### 요구 사항
- Windows 10/11
- Unreal Engine **5.4**
- Visual Studio 2022 (Game development with C++ 워크로드)

### 절차
1. 본 저장소를 클론
2. 아래 **에셋 다운로드** 링크에서 `Content/` 에셋을 받아 프로젝트 루트에 배치
3. `TPSProject.uproject` 우클릭 → **Generate Visual Studio project files**
4. `TPSProject.sln` 을 Visual Studio 2022로 열고 **Development Editor / Win64** 빌드
5. 에디터 실행 후 `Play` (멀티플레이 테스트 시 `Number of Players` ≥ 2)

---

## 에셋 다운로드

Content 에셋(메시/텍스처/사운드/애니메이션 등)은 용량 문제로 Git이 아닌 Google Drive로 관리합니다.

🔗 https://drive.google.com/drive/folders/1VfABuVnT1Gg2V05NfEVApOPhWiwpaBKW?usp=drive_link

---

## 개발자

**wonjin**
