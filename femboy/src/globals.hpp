#pragma once
#include "includes.h"
#include "rbx/classes.hpp"

/*
 * Global state and configuration for the external
 * All settings can be modified via the in-game menu
 */

namespace globals
{
	// ============================================================================
	// ROBLOX INSTANCES
	// ============================================================================
	
	inline std::string username = "Player";
	inline bool focused = false;
	inline rbx::rinstance datamodel;
	inline rbx::rinstance mouse_service;
	inline rbx::rinstance visualengine;
	inline rbx::rinstance players;
	inline rbx::rinstance workspace;
	inline rbx::rvector3 cameraposition;
	inline uint64_t gameid;
	inline rbx::rvector3 aimbotbodypart;
	inline ID3D11Device* overlaydevice = nullptr;
	
	// ============================================================================
	// AUDIO SETTINGS
	// ============================================================================
	
	inline bool hitlogse = true;
	inline bool hitsound = false;
	inline int selectedhitsound = 0;
	
	// ============================================================================
	// AUTHENTICATION
	// ============================================================================
	
	namespace auth
	{
		inline std::string key;
		inline bool authenticated = true;
	}
	
	// ============================================================================
	// MENU & INPUT
	// ============================================================================
	
	inline int menukey = VK_INSERT;
	inline bool menu_open = false;
	
	// ============================================================================
	// ESP SETTINGS
	// ============================================================================
	
	namespace esp
	{
		inline bool watermark = true;
		inline bool box3d = false;
		inline int font = 0;
		inline int watermarktype = 0;
		inline bool playerlist = true;
		inline bool explorer = true;
		inline bool enabled = true;
		inline bool knifeboiesp = false;
		inline bool shield_bar = false;
		inline bool selfesp = false;
		inline bool box = true;
		inline bool boxfilled = false;
		inline bool health = true;
		inline bool name = true;
		inline bool distance = true;
		inline bool tool = false;
		inline bool chams = false;
		inline bool glow = false;
		inline bool chamsoutline = false;
		inline bool tracers = false;
		inline bool headdot = false;
		inline bool headdotfilled = false;
		inline bool fovfilled = false;
		inline bool teamcheck = true;
		inline bool flame_bar = false;
		inline bool skeleton = false;
		inline bool aimbottracer = false;
		inline int maxdistance = 1000;
		
		namespace colors
		{
			inline float box[3] = { 1.0f, 1.0f, 1.0f };
			inline float aimbottracer[3] = { 1.0f, 0.0f, 0.0f };
			inline float tracers[3] = { 0.0f, 1.0f, 1.0f };
			inline float boxfilled[4] = { 1.0f, 1.0f, 1.0f, 0.5f };
			inline float healthbar[3] = { 0.04f, 0.98f, 0.13f };
			inline float name[3] = { 1.0f, 1.0f, 1.0f };
			inline float distance[3] = { 1.0f, 1.0f, 1.0f };
			inline float tool[3] = { 1.0f, 1.0f, 1.0f };
			inline float headdot[3] = { 1.0f, 1.0f, 1.0f };
			inline float skeleton[3] = { 1.0f, 1.0f, 1.0f };
			inline float chams[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			inline float chamsoutline[3] = { 0.0f, 0.0f, 0.0f };
			inline float fov[3] = { 1.0f, 1.0f, 1.0f };
			inline float fovsilent[3] = { 1.0f, 1.0f, 1.0f };
			inline float fovfilled[4] = { 1.0f, 1.0f, 1.0f, 0.3f };
			inline float fovfilledsilent[4] = { 1.0f, 1.0f, 1.0f, 0.2f };
			inline float headdotfilled[4] = { 1.0f, 1.0f, 1.0f, 0.5f };
		}
	}
	
	// ============================================================================
	// AIMBOT SETTINGS
	// ============================================================================
	
	namespace aimbot
	{
		inline int aimbotkey = VK_RBUTTON;
		inline int minimumdsitacne = 10;
		inline bool togglekey = false;
		inline bool teamcheck = true;
		inline bool enabled = true;
		inline bool disableoutoffov = false;
		inline bool prediction = false;
		inline int aimtype = 0;
		inline int aimpart = 0;  // 0=Head, 1=Chest, 2=Neck
		inline bool drawfov = true;
		inline int fov = 150;
		inline int predx = 15;
		inline int predy = 15;
		inline int smoth = 10;
		inline int smothx = 10;
		inline int smothy = 10;
	}
	
	// ============================================================================
	// SILENT AIM SETTINGS
	// ============================================================================
	
	namespace silentaim
	{
		inline int aimbotkey = VK_LBUTTON;
		inline bool togglekey = false;
		inline bool teamcheck = true;
		inline bool enabled = false;
		inline bool disableoutoffov = false;
		inline bool prediction = false;
		inline int aimpart = 0;
		inline bool drawfov = true;
		inline bool filledfov = true;
		inline int fov = 100;
		inline int predx = 5;
		inline int predy = 5;
	}
	
	// ============================================================================
	// TRIGGER BOT SETTINGS
	// ============================================================================
	
	namespace triggerbot
	{
		inline int triggerbotkey = VK_LBUTTON;
		inline bool togglekey = false;
		inline bool teamcheck = true;
		inline bool enabled = false;
		inline int delay = 50;
	}
	
	// ============================================================================
	// HVH (Player vs Player) SETTINGS
	// ============================================================================
	
	namespace HVH
	{
		inline bool enabled = false;
		inline bool rapidfire = false;
		inline bool antistomp = false;
		inline bool spamtp = false;
		inline bool antiaim = false;
	}
	
	// ============================================================================
	// MOVEMENT HACKS SETTINGS
	// ============================================================================
	
	namespace movement
	{
		// CFrame Movement
		inline bool cframe = false;
		inline int cspeed = 100;
		inline int caimbotkey = 'W';
		inline bool ctogglekey = false;
		
		// Flight
		inline bool fly = false;
		inline float fspeed = 10.0f;
		inline int faimbotkey = VK_SPACE;
		inline bool ftogglekey = false;
		
		// Speed
		inline bool speedhack = false;
		inline float speedvalue = 16.0f;
		
		// Noclip
		inline bool noclip = false;
	}
	
	// ============================================================================
	// STREAM PROOF & MISC
	// ============================================================================
	
	inline bool streamproof = false;
	
}
