#include "includes.h"

// Memory interface
memify mem(("RobloxPlayerBeta.exe"));

// ============================================================================
// STRING READING UTILITIES
// ============================================================================

std::string readstring(std::uint64_t address)
{
    std::string string;
    char character = 0;
    int char_size = sizeof(character);
    int offset = 0;
    string.reserve(204);

    while (offset < 200)
    {
        character = mem.Read<char>(address + offset);

        if (character == 0)
            break;

        offset += char_size;
        string.push_back(character);
    }

    return string;
}

std::string readstringAlt(std::uint64_t string)
{
    const auto length = mem.Read<int>(string + 0x18);

    if (length >= 16u)
    {
        const auto New = mem.Read<std::uint64_t>(string);
        return readstring(New);
    }
    else
    {
        const auto Name = readstring(string);
        return Name;
    }
}

// ============================================================================
// AUTO-RESCAN THREAD
// ============================================================================

void autorescan()
{
    while (true)
    {
        uintptr_t fakedatamodel = mem.Read<uintptr_t>(mem.GetBase(("RobloxPlayerBeta.exe")) + 0x690D168);
        auto currentdtmodel = mem.Read<rbx::rinstance>(fakedatamodel + 0x1B8);
        if (currentdtmodel != globals::datamodel)
        {
            printf(("[femboy] rescanning\n"));
            rbx::rescan();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

// ============================================================================
// MAIN ENTRY POINT
// ============================================================================

int main()
{
    // Hide console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    // Initialize Roblox instances
    uintptr_t fakedatamodel = mem.Read<uintptr_t>(mem.GetBase(("RobloxPlayerBeta.exe")) + 0x651E3B8);
    globals::datamodel = mem.Read<rbx::rinstance>(fakedatamodel + 0x1b8);
    globals::visualengine = mem.Read<rbx::rinstance>(mem.GetBase(("RobloxPlayerBeta.exe")) + 0x636BDE8);

    // Get essential services
    globals::players = globals::datamodel.FindFirstChildOfClass(("Players"));
    globals::workspace = globals::datamodel.FindFirstChildOfClass(("Workspace"));
    globals::mouse_service = globals::datamodel.FindFirstChild(("MouseService"));

    // Start threads
    std::thread(rbx::cache::thread).detach();
    std::thread(hacks::aimbot::thread).detach();
    std::thread(hacks::aimbot::sthread).detach();
    std::thread(hacks::movement::thread).detach();
    printf(("[femboy] Initialization complete. Press INSERT to open menu.\n"));
    
    // Log game info
    std::cout << "[femboy] GameID: " << globals::datamodel.GameID() << std::endl;
    globals::gameid = globals::datamodel.GameID();
    
    // Start utility threads
    std::thread(autorescan).detach();
    std::thread(overlay::thread).detach();

    // Main loop
    while (true)
    {
        // Check if Roblox is focused
        globals::focused = GetForegroundWindow() == FindWindowA(0, ("Roblox"));
        
        // Exit if Roblox closes
        if (FindWindowA(0, ("Roblox")) == NULL) {
            exit(0);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}

// ============================================================================
// ROBLOX INSTANCE METHODS
// ============================================================================

void rbx::rescan()
{
    hacks::lua::callback_rescan();
    uintptr_t fakedatamodel = mem.Read<uintptr_t>(mem.GetBase(("RobloxPlayerBeta.exe")) + 0x651E3B8);
    globals::datamodel = mem.Read<rbx::rinstance>(fakedatamodel + 0x1b8);
    globals::visualengine = mem.Read<rbx::rinstance>(mem.GetBase(("RobloxPlayerBeta.exe")) + 0x636BDE8);

    globals::players = globals::datamodel.FindFirstChildOfClass(("Players"));
    globals::workspace = globals::datamodel.FindFirstChildOfClass(("Workspace"));
    globals::mouse_service = globals::datamodel.FindFirstChild(("MouseService"));
    globals::gameid = globals::datamodel.GameID();
}

rbx::rvector2 rbx::WorldToScreen(rbx::rvector3 world, rbx::rvector2 dimensions, rbx::rmatrix4 viewmatrix)
{
    rbx::quaternion quaternion;

    quaternion.x = (world.x * viewmatrix.data[0]) + (world.y * viewmatrix.data[1]) + (world.z * viewmatrix.data[2]) + viewmatrix.data[3];
    quaternion.y = (world.x * viewmatrix.data[4]) + (world.y * viewmatrix.data[5]) + (world.z * viewmatrix.data[6]) + viewmatrix.data[7];
    quaternion.z = (world.x * viewmatrix.data[8]) + (world.y * viewmatrix.data[9]) + (world.z * viewmatrix.data[10]) + viewmatrix.data[11];
    quaternion.w = (world.x * viewmatrix.data[12]) + (world.y * viewmatrix.data[13]) + (world.z * viewmatrix.data[14]) + viewmatrix.data[15];

    if (quaternion.w < 0.1f)
        return { -1, -1 };

    rbx::rvector3 ndc{};

    ndc.x = quaternion.x / quaternion.w;
    ndc.y = quaternion.y / quaternion.w;
    ndc.z = quaternion.z / quaternion.w;

    rbx::rvector2 screenPos = {
        (dimensions.x / 2 * ndc.x) + (dimensions.x / 2),
        -(dimensions.y / 2 * ndc.y) + (dimensions.y / 2)
    };

    if (screenPos.x < 0 || screenPos.x > dimensions.x || screenPos.y < 0 || screenPos.y > dimensions.y)
        return { -1, -1 };

    return screenPos;
}

std::string rbx::rinstance::GetName()
{
    if (!this->self)
        return ("RINSTANCE_NONAME");

    const auto nameptr = mem.Read<std::uint64_t>(this->self + rbx::offests::Name);
    if (nameptr)
        return readstringAlt(nameptr);
    return ("RINSTANCE_NONAME");
}

std::string rbx::rinstance::GetClass()
{
    if (!this->self)
        return ("RINSTANCE_NOCLASSNAME");

    auto A = mem.Read<std::uint64_t>(this->self + 0x18);
    if (!A)
        return ("RINSTANCE_NOCLASSNAME");

    auto B = mem.Read<std::uint64_t>(A + 0x8);
    if (B)
        return readstringAlt(B);
    return ("RINSTANCE_NOCLASSNAME");
}

std::vector<rbx::rinstance> rbx::rinstance::GetChildren()
{
    std::vector<rbx::rinstance> container;

    if (!this->self)
        return container;

    auto start = mem.Read<std::uint64_t>(this->self + rbx::offests::Children);
    if (!start)
        return container;

    auto end = mem.Read<std::uint64_t>(start + rbx::offests::ChildSize);
    if (!end)
        return container;

    for (auto instances = mem.Read<std::uint64_t>(start); instances != end; instances += 16) {
        if (instances > 1099511627776 && instances < 3298534883328) {
            container.emplace_back(mem.Read<rbx::rinstance>(instances));
        }
    }
    return container;
}

rbx::rinstance rbx::rinstance::FindFirstChild(const std::string& Name)
{
    if (!this->self || Name.empty())
        return rbx::rinstance();

    std::vector<rbx::rinstance> children = this->GetChildren();

    for (auto& object : children)
    {
        if (object.GetName() == Name)
        {
            return object;
        }
    }
    return rbx::rinstance();
}

rbx::rinstance rbx::rinstance::FindFirstChildOfClass(const std::string& Name)
{
    if (!this->self || Name.empty())
        return rbx::rinstance();

    std::vector<rbx::rinstance> children = this->GetChildren();

    for (auto& object : children)
    {
        if (object.GetClass() == Name)
        {
            return object;
        }
    }
    return rbx::rinstance();
}

std::uint64_t rbx::rinstance::GameID()
{
    if (!this->self)
        return 0;

    return mem.Read<std::uint64_t>(this->self + rbx::offests::GameId);
}
