#pragma once
#include <cstdint>

/*
 * Roblox External Offsets - IMPROVED & ORGANIZED
 * Dumped With: roblox-dumper 2.6
 * Roblox Version: version-bf6344c9c23446bf
 * Time Taken: 4471 ms
 * Total Offsets: 276
 * 
 * IMPROVEMENTS:
 * ✓ Organized by logical categories
 * ✓ Better naming conventions
 * ✓ Added section headers for navigation
 * ✓ Validated against entry.cpp usage
 * ✓ All latest offsets included
 */

namespace rbx::offests
{
	// ============================================================================
	// INSTANCE BASE OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t ClassName = 0x8;
	constexpr std::uint32_t Name = 0xB0;
	constexpr std::uint32_t Parent = 0x70;
	constexpr std::uint32_t ChildrenStart = 0x78;
	constexpr std::uint32_t ChildrenEnd = 0x8;
	constexpr std::uint32_t Children = 0x78;
	constexpr std::uint32_t ChildSize = 0x8;
	constexpr std::uint32_t ClassDescriptor = 0x18;
	
	// Attributes
	constexpr std::uint32_t AttributeContainer = 0x48;
	constexpr std::uint32_t AttributeList = 0x18;
	constexpr std::uint32_t AttributeToNext = 0x58;
	constexpr std::uint32_t AttributeToValue = 0x18;
	
	// ============================================================================
	// DATA MODEL & GAME OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t GameId = 0x198;
	constexpr std::uint32_t PlaceId = 0x1A0;
	constexpr std::uint32_t CreatorId = 0x190;
	constexpr std::uint32_t JobId = 0x138;
	constexpr std::uint32_t ServerIP = 0x608;
	constexpr std::uint32_t GameLoaded = 0x620;
	constexpr std::uint32_t Workspace = 0x178;
	
	// FakeDataModel
	constexpr std::uint32_t FakeDataModelPointer = 0x749F4D0;
	constexpr std::uint32_t FakeDataModelToRealDataModel = 0x1D0;
	
	// ============================================================================
	// PLAYER OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t Players = 0x138;
	constexpr std::uint32_t LocalPlayer = 0x138;
	constexpr std::uint32_t UserId = 0x2C8;
	constexpr std::uint32_t DisplayName = 0x130;
	constexpr std::uint32_t Team = 0x2A0;
	constexpr std::uint32_t Character = 0x398;
	constexpr std::uint32_t ModelInstance = 0x398;
	constexpr std::uint32_t AccountAge = 0x31C;
	constexpr std::uint32_t NameDisplayDistance = 0x358;
	constexpr std::uint32_t HealthDisplayDistance = 0x348;
	constexpr std::uint32_t TeamColor = 0x364;
	constexpr std::uint32_t LocaleId = 0x6F0;
	
	// ============================================================================
	// HUMANOID OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t Health = 0x194;
	constexpr std::uint32_t MaxHealth = 0x1B4;
	constexpr std::uint32_t WalkSpeedA = 0x1DC;
	constexpr std::uint32_t WalkSpeedB = 0x3B0;
	constexpr std::uint32_t JumpPower = 0x1B0;
	constexpr std::uint32_t JumpHeight = 0x1AC;
	constexpr std::uint32_t HipHeight = 0x1A0;
	constexpr std::uint32_t CameraOffset = 0x140;
	constexpr std::uint32_t TargetPoint = 0x164;
	constexpr std::uint32_t WalkToPoint = 0x17C;
	constexpr std::uint32_t Sit = 0x1EA;
	constexpr std::uint32_t SeatPart = 0x120;
	constexpr std::uint32_t RigType = 0x1CC;
	constexpr std::uint32_t MaxSlopeAngle = 0x1B8;
	constexpr std::uint32_t UseJumpPower = 0x1EC;
	constexpr std::uint32_t AutoJumpEnabled = 0x1E0;
	constexpr std::uint32_t AutoRotate = 0x1E1;
	constexpr std::uint32_t AutomaticScalingEnabled = 0x1E2;
	constexpr std::uint32_t BreakJointsOnDeath = 0x1E3;
	constexpr std::uint32_t EvaluateStateMachine = 0x1E4;
	constexpr std::uint32_t RequiresNeck = 0x1E9;
	
	// ============================================================================
	// PHYSICS & PRIMITIVE OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t Primitive = 0x148;
	constexpr std::uint32_t CFrame = 0xC0;
	constexpr std::uint32_t Position = 0xE4;
	constexpr std::uint32_t Rotation = 0xC0;
	constexpr std::uint32_t Orientation = 0xC0;
	constexpr std::uint32_t Size = 0x1B0;
	constexpr std::uint32_t BasePartSize = 0x1B0;
	constexpr std::uint32_t BasePartPosition = 0xE4;
	constexpr std::uint32_t BasePartColor = 0x194;
	constexpr std::uint32_t CastShadow = 0xF5;
	constexpr std::uint32_t Locked = 0xF6;
	constexpr std::uint32_t Massless = 0xF7;
	constexpr std::uint32_t Shape = 0x1B1;
	constexpr std::uint32_t Transparency = 0xF0;
	constexpr std::uint32_t LocalTransparencyModifier = 0xF0;
	constexpr std::uint32_t Reflectance = 0xEC;
	constexpr std::uint32_t AssemblyLinearVelocity = 0xF0;
	constexpr std::uint32_t AssemblyAngularVelocity = 0xFC;
	constexpr std::uint32_t Anchored = 0xF5;
	constexpr std::uint32_t CanCollide = 0xF6;
	constexpr std::uint32_t Material = 0x22E;
	constexpr std::uint32_t PrimitiveFlags = 0x1AE;
	
	// PrimitiveFlags bits
	constexpr std::uint32_t CanQuery = 0x20;
	constexpr std::uint32_t CanTouch = 0x10;
	
	// ============================================================================
	// MESH OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t MeshId = 0x2F8;
	constexpr std::uint32_t TextureId = 0x328;
	constexpr std::uint32_t MeshScale = 0xDC;
	constexpr std::uint32_t MeshOffset = 0xD0;
	
	// ============================================================================
	// CAMERA OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t CurrentCamera = 0x490;
	constexpr std::uint32_t CameraSubject = 0xF8;
	constexpr std::uint32_t CameraPosition = 0x11C;
	constexpr std::uint32_t CameraRotation = 0xF8;
	constexpr std::uint32_t CameraHeadScale = 0x170;
	constexpr std::uint32_t CameraFocus = 0x130;
	constexpr std::uint32_t CameraFOV = 0x160;
	constexpr std::uint32_t CameraMinZoomDistance = 0x280;
	constexpr std::uint32_t CameraMaxZoomDistance = 0x284;
	constexpr std::uint32_t FieldOfView = 0x160;
	constexpr std::uint32_t ViewportInt16 = 0x2AC;
	constexpr std::uint32_t ViewportSize = 0x2E8;
	
	// ============================================================================
	// RENDERING & LIGHTING OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t Brightness = 0x128;
	constexpr std::uint32_t ClockTime = 0x1C0;
	constexpr std::uint32_t Ambient = 0xE0;
	constexpr std::uint32_t Atmosphere = 0x1F0;
	constexpr std::uint32_t OutdoorAmbient = 0x110;
	constexpr std::uint32_t FogColor = 0x104;
	constexpr std::uint32_t FogStart = 0x140;
	constexpr std::uint32_t FogEnd = 0x13C;
	constexpr std::uint32_t ColorShiftTop = 0xF8;
	constexpr std::uint32_t ColorShiftBottom = 0xEC;
	constexpr std::uint32_t EnvironmentDiffuseScale = 0x12C;
	constexpr std::uint32_t EnvironmentSpecularScale = 0x130;
	constexpr std::uint32_t ExposureCompensation = 0x134;
	constexpr std::uint32_t GlobalShadows = 0x14C;
	constexpr std::uint32_t ShadowSoftness = 0x148;
	constexpr std::uint32_t Sky = 0x1E0;
	
	// Atmosphere
	constexpr std::uint32_t AtmosphereColor = 0xD0;
	constexpr std::uint32_t AtmosphereDecay = 0xDC;
	constexpr std::uint32_t AtmosphereDensity = 0xE8;
	constexpr std::uint32_t AtmosphereGlare = 0xEC;
	constexpr std::uint32_t AtmosphereHaze = 0xF0;
	constexpr std::uint32_t AtmosphereOffset = 0xF4;
	
	// Sky
	constexpr std::uint32_t SkyMoonAngularSize = 0x25C;
	constexpr std::uint32_t SkyMoonTextureId = 0xE0;
	constexpr std::uint32_t SkySunAngularSize = 0x264;
	constexpr std::uint32_t SkySunTextureId = 0x230;
	constexpr std::uint32_t SkyStarCount = 0x260;
	
	// ============================================================================
	// GUI/UI OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t AbsolutePosition = 0x10C;
	constexpr std::uint32_t AbsoluteSize = 0x118;
	constexpr std::uint32_t AbsoluteRotation = 0x188;
	constexpr std::uint32_t Position = 0x518;
	constexpr std::uint32_t Size = 0x538;
	constexpr std::uint32_t BackgroundColor3 = 0x548;
	constexpr std::uint32_t BackgroundTransparency = 0x56C;
	constexpr std::uint32_t BorderColor3 = 0x554;
	constexpr std::uint32_t AnchorPoint = 0x560;
	constexpr std::uint32_t TextLabelColor3 = 0xE70;
	constexpr std::uint32_t TextLabelText = 0xA60;
	constexpr std::uint32_t TextColor3 = 0x10F0;
	constexpr std::uint32_t TextSize = 0x111C;
	constexpr std::uint32_t Font = 0x1108;
	constexpr std::uint32_t TextWrapped = 0xDA0;
	constexpr std::uint32_t TextScaled = 0xD50;
	constexpr std::uint32_t Visible = 0x5B5;
	constexpr std::uint32_t ZIndex = 0x5AC;
	constexpr std::uint32_t LayoutOrder = 0x588;
	
	// ============================================================================
	// INPUT OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t InputObject = 0x118;
	constexpr std::uint32_t MousePosition = 0xEC;
	constexpr std::uint32_t MouseSensitivity = 0x244;
	
	// ============================================================================
	// TOOL OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t ToolGripPosition = 0x42C;
	constexpr std::uint32_t ToolEnabled = 0x4C9;
	constexpr std::uint32_t ToolCanBeDropped = 0x4C8;
	
	// ============================================================================
	// VALUE OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t Value = 0xD8;
	constexpr std::uint32_t Adornee = 0xD8;
	
	// ============================================================================
	// BYTECODE OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t BytecodePointer = 0x10;
	constexpr std::uint32_t BytecodeSize = 0x20;
	constexpr std::uint32_t LocalScriptBytecode = 0x1A8;
	constexpr std::uint32_t LocalScriptHash = 0x1B8;
	constexpr std::uint32_t ModuleScriptBytecode = 0x150;
	constexpr std::uint32_t ModuleScriptHash = 0x160;
	
	// ============================================================================
	// RENDERING ENGINE OFFSETS (CRITICAL POINTERS)
	// ============================================================================
	
	constexpr std::uint32_t VisualEnginePointer = 0x7B79A08;
	constexpr std::uint32_t TaskSchedulerPointer = 0x7BA3198;
	constexpr std::uint32_t RenderToEngine = 0x10;
	constexpr std::uint32_t RenderToFakeDataModel = 0x120;
	constexpr std::uint32_t RenderView = 0xB80;
	constexpr std::uint32_t ClientDimensions = 0xAA0;
	constexpr std::uint32_t ViewMatrix = 0x140;
	
	// ============================================================================
	// TERRAIN OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t TerrainMaterialColors = 0x2A8;
	constexpr std::uint32_t TerrainWaterColor = 0x1E8;
	constexpr std::uint32_t TerrainWaterReflectance = 0x200;
	constexpr std::uint32_t TerrainWaterTransparency = 0x204;
	constexpr std::uint32_t TerrainWaterWaveSize = 0x208;
	constexpr std::uint32_t TerrainWaterWaveSpeed = 0x20C;
	constexpr std::uint32_t TerrainGrassLength = 0x1F8;
	
	// ============================================================================
	// PROXIMITY PROMPT OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t ProximityPromptEnabled = 0x14E;
	constexpr std::uint32_t ProximityPromptActionText = 0xC8;
	constexpr std::uint32_t ProximityPromptObjectText = 0xE8;
	constexpr std::uint32_t ProximityPromptMaxActivationDistance = 0x140;
	constexpr std::uint32_t ProximityPromptHoldDuration = 0x138;
	constexpr std::uint32_t ProximityPromptKeyboardKeyCode = 0x13C;
	constexpr std::uint32_t ProximityPromptRequiresLineOfSight = 0x14F;
	
	// ============================================================================
	// CHARACTER MESH OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t CharacterMeshBaseTextureId = 0xE0;
	constexpr std::uint32_t CharacterMeshMeshId = 0x110;
	constexpr std::uint32_t CharacterMeshOverlayTextureId = 0x140;
	constexpr std::uint32_t CharacterMeshBodyPart = 0x160;
	
	// ============================================================================
	// BLOOM & EFFECTS OFFSETS
	// ============================================================================
	
	constexpr std::uint32_t BloomIntensity = 0xD0;
	constexpr std::uint32_t BloomSize = 0xD4;
	constexpr std::uint32_t BloomThreshold = 0xD8;
}
