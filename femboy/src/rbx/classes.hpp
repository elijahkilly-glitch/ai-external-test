#pragma once
#include <string>
#include <vector>

namespace rbx
{
	void rescan();
	
	// ============================================================================
	// VECTOR STRUCTURES
	// ============================================================================
	
	struct rvector2 final {
		float x{ 0.0f }, y{ 0.0f };

		rvector2 operator+(const rvector2& rhs) const {
			return { x + rhs.x, y + rhs.y };
		}

		rvector2 operator-(const rvector2& rhs) const {
			return { x - rhs.x, y - rhs.y };
		}

		rvector2 operator*(float scalar) const {
			return { x * scalar, y * scalar };
		}
	};

	struct rvector3 final {
		float x{ 0.0f }, y{ 0.0f }, z{ 0.0f };

		rvector3 operator+(const rvector3& rhs) const {
			return { x + rhs.x, y + rhs.y, z + rhs.z };
		}

		rvector3 operator-(const rvector3& rhs) const {
			return { x - rhs.x, y - rhs.y, z - rhs.z };
		}

		rvector3 operator*(float scalar) const {
			return { x * scalar, y * scalar, z * scalar };
		}
	};

	struct quaternion final { float x, y, z, w; };
	struct rmatrix4 final { float data[16]; };
	struct rmatrix3 final { float data[9]; };

	// ============================================================================
	// CFRAME STRUCTURE
	// ============================================================================
	
	struct CFrame
	{
		rvector3 right_vector = { 1, 0, 0 };
		rvector3 up_vector = { 0, 1, 0 };
		rvector3 back_vector = { 0, 0, 1 };
		rvector3 position = { 0, 0, 0 };

		CFrame() = default;
		CFrame(rvector3 position) : position{ position } {}
	};

	rvector2 WorldToScreen(rvector3 world, rvector2 dimensions, rmatrix4 viewmatrix);

	// ============================================================================
	// ROBLOX INSTANCE CLASS
	// ============================================================================
	
	class rinstance final
	{
		public:
			std::uint64_t self;

			bool operator==(const rinstance& other) const {
				return this->self == other.self;
			}
			
			// Instance methods
			std::string GetName();
			std::string GetClass();
			std::vector<rinstance> GetChildren();
			rinstance FindFirstChild(const std::string& Name);
			rinstance FindFirstChildOfClass(const std::string& Name);
			rinstance Parent() const;
			std::uint64_t GameID();
			
			// Physics methods
			rvector3 GetPartPosition();
			void SetPartPosition(rvector3 position);
			rvector3 GetPartVelocity();
			void SetPartVelocity(rvector3 velocity);
			rmatrix3 GetPartRotation();
			void SetCFrame(const CFrame& cf);
			rvector3 GetSize();
			void SetPartSize(rvector3 value);
			
			// Humanoid methods
			float Health();
			void SetHealth(float value);
			float MaxHealth();
			void SetWalkSpeed(float speed);
			int32_t RigType();
			
			// Property methods
			uint32_t GetColor3() const;
			void SetPartCanCollide(bool value);
			void SetPartTransperancy(float value);
			
			// Camera methods
			rvector3 GetCameraPosition();
			rmatrix3 GetCameraRotation();
			void WriteCameraRotations(rmatrix3 Rotation);
			rinstance GetCamera();
			
			// Utility methods
			rvector3 GetMoveDirection() const;
			rinstance GetLocalPlayer();
			rinstance GetCharacter();
			rinstance Team();
			rinstance Adornee();
			
			// Value methods
			double DoubleValue();
			double SetDoubleValue(double value);
			void SetBoolValue(bool value);
			bool BoolValue();
			int IntValue();
			
			// GUI methods
			std::string TextLabelText();
			rvector2 Dimensions();
			rmatrix4 ViewMatrix();
			
			// Input/Frame methods
			void frameposX(uint64_t pos);
			void frameposY(uint64_t pos);
	};
	
	void freeaim(rvector2 pos);
	void ApplyFrame(rvector2 targetpos, rvector2 dimensions, const POINT& cursorpoint);
}

// ============================================================================
// HACKS NAMESPACES (Forward declarations)
// ============================================================================

namespace hacks
{
	namespace aimbot
	{
		void thread();
		void sthread();
	}
	
	namespace movement
	{
		void thread();
	}
	
	namespace lua
	{
		void callback_rescan();
		void setup();
	}
}

namespace rbx
{
	namespace cache
	{
		struct LocalPlayer
		{
			rbx::rinstance aim;
			rbx::rinstance hc_aim;
			rbx::rinstance rh_aim;
			rbx::rinstance kh_aim;
		};
		
		inline LocalPlayer localplayer;
		void thread();
	}
}

namespace overlay
{
	void thread();
}
