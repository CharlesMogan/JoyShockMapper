#pragma once

#include "JSMVersion.h"
#include "PlatformDefinitions.h"
#include "magic_enum.hpp"

#include <map>
#include <functional>

// This header file is meant to be included among all core JSM source files
// And as such it should contain only constants, types and functions related to them

using namespace std; // simplify all std calls

// input string parameters should be const references.
typedef const string &in_string;

// Reused OS typedefs
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

// https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
// Only use undefined keys from the above list for JSM custom commands
constexpr WORD V_WHEEL_UP = 0x03; // Here I intentionally overwride VK_CANCEL because breaking a process with a keybind is not something we want to do
constexpr WORD V_WHEEL_DOWN = 0x07; // I want all mouse bindings to be contiguous IDs for ease to distinguish
constexpr WORD NO_HOLD_MAPPED = 0x0A; // Empty mapping, which is different form no mapping for combo presses
constexpr WORD CALIBRATE = 0x0B;
constexpr WORD GYRO_INV_X = 0x88;
constexpr WORD GYRO_INV_Y = 0x89;
constexpr WORD GYRO_INVERT = 0x8A;
constexpr WORD GYRO_OFF_BIND = 0x8B; // Not to be confused with settings GYRO_ON and GYRO_OFF
constexpr WORD GYRO_ON_BIND = 0x8C;  // Those here are bindings

// All enums should have an INVALID field for proper use with templated << and >> operators

enum class ButtonID
{
	INVALID =		-2, // Represents an error in user input
	NONE,		// = -1  Represents no button when explicitely stated by the user. Not to be confused with NO_HOLD_MAPPED which is no action bound.
	UP,			// = 0
	DOWN,		// = 1
	LEFT,		// = 2
	RIGHT,		// = 3
	L,			// = 4
	ZL,			// = 5
	MINUS,		// = 6
	CAPTURE,	// = 7
	E,			// = 8
	S,			// = 9
	N,			// = 10
	W,			// = 11
	R,			// = 12
	ZR,			// = 13
	PLUS,		// = 14
	HOME,		// = 15
	SL,			// = 16
	SR,			// = 17
	L3,			// = 18
	R3,			// = 19
	LUP,		// = 20
	LDOWN,		// = 21
	LLEFT,		// = 22
	LRIGHT,		// = 23
	LRING,		// = 24
	RUP,		// = 25
	RDOWN,		// = 26
	RLEFT,		// = 27
	RRIGHT,		// = 28
	RRING,		// = 29
	ZLF,		// = 30  FIRST_ANALOG_TRIGGER
				// insert more analog triggers here
	ZRF,		// = 31 // LAST_ANALOG_TRIGGER
	SIZE,		// = 32
};

enum class SettingID
{
	INVALID = -2,			// Represents an error in user input
	MIN_GYRO_SENS = int(ButtonID::SIZE) + 1,
	MAX_GYRO_SENS,			// = 34
	MIN_GYRO_THRESHOLD,		// = 35
	MAX_GYRO_THRESHOLD,		// = 36
	STICK_POWER,			// = 37
	STICK_SENS,				// = 38
	REAL_WORLD_CALIBRATION, // = 39
	IN_GAME_SENS,			// = 40
	TRIGGER_THRESHOLD,		// = 41
	RESET_MAPPINGS,			// = 42
	NO_GYRO_BUTTON,			// = 43
	LEFT_STICK_MODE,		// = 44
	RIGHT_STICK_MODE,		// = 45
	GYRO_OFF,				// = 46
	GYRO_ON,				// = 47
	STICK_AXIS_X,			// = 48
	STICK_AXIS_Y,			// = 49
	GYRO_AXIS_X,			// = 50
	GYRO_AXIS_Y,			// = 51
	RECONNECT_CONTROLLERS,	// = 52
	COUNTER_OS_MOUSE_SPEED, // = 53
	IGNORE_OS_MOUSE_SPEED,	// = 54
	JOYCON_GYRO_MASK,		// = 55
	GYRO_SENS,				// = 56
	FLICK_TIME,				// = 57
	GYRO_SMOOTH_THRESHOLD,	// = 58
	GYRO_SMOOTH_TIME,		// = 59
	GYRO_CUTOFF_SPEED,		// = 60
	GYRO_CUTOFF_RECOVERY,	// = 61
	STICK_ACCELERATION_RATE, // = 62
	STICK_ACCELERATION_CAP, // = 63
	STICK_DEADZONE_INNER,	// = 64
	STICK_DEADZONE_OUTER,	// = 65
	CALCULATE_REAL_WORLD_CALIBRATION, // = 66
	FINISH_GYRO_CALIBRATION, // = 67
	RESTART_GYRO_CALIBRATION, // = 68
	MOUSE_X_FROM_GYRO_AXIS, // = 69
	MOUSE_Y_FROM_GYRO_AXIS, // = 70
	ZR_MODE,				// = 71
	ZL_MODE,				// = 72
	AUTOLOAD,				// = 73
	HELP,					// = 74
	WHITELIST_SHOW,			// = 75
	WHITELIST_ADD,			// = 76
	WHITELIST_REMOVE,		// = 77
	LEFT_RING_MODE,			// = 78
	RIGHT_RING_MODE,		// = 79
	MOUSE_RING_RADIUS,		// = 80
	SCREEN_RESOLUTION_X,	// = 81
	SCREEN_RESOLUTION_Y,	// = 82
	ROTATE_SMOOTH_OVERRIDE, // = 83
	FLICK_SNAP_MODE,		// = 84
	FLICK_SNAP_STRENGTH,	// = 85
	TRIGGER_SKIP_DELAY,
	TURBO_PERIOD,
	HOLD_PRESS_TIME,
	SIM_PRESS_WINDOW, // Unchorded setting
	DBL_PRESS_WINDOW,// Unchorded setting
};

// constexpr are like #define but with respect to typeness
constexpr int MAPPING_SIZE = int(ButtonID::SIZE);
constexpr int FIRST_ANALOG_TRIGGER = int(ButtonID::ZLF);
constexpr int LAST_ANALOG_TRIGGER = int(ButtonID::ZRF);
constexpr int NUM_ANALOG_TRIGGERS = int(LAST_ANALOG_TRIGGER) - int(FIRST_ANALOG_TRIGGER) + 1;
constexpr float MAGIC_TAP_DURATION = 40.0f; // in milliseconds
constexpr float MAGIC_EXTENDED_TAP_DURATION = 500.0f; // in milliseconds

enum class RingMode { OUTER, INNER, INVALID };
enum class StickMode { NO_MOUSE, AIM, FLICK, FLICK_ONLY, ROTATE_ONLY, MOUSE_RING, MOUSE_AREA, OUTER_RING, INNER_RING, INVALID };
enum class FlickSnapMode { NONE, FOUR, EIGHT, INVALID };
enum class AxisMode { STANDARD = 1, INVERTED = -1, INVALID = 0 }; // valid values are true!
enum class TriggerMode { NO_FULL, NO_SKIP, MAY_SKIP, MUST_SKIP, MAY_SKIP_R, MUST_SKIP_R, INVALID };
enum class GyroAxisMask { NONE = 0, X = 1, Y = 2, Z = 4, INVALID = 8 };
enum class JoyconMask { USE_BOTH, IGNORE_LEFT, IGNORE_RIGHT, IGNORE_BOTH, INVALID };
enum class GyroIgnoreMode { BUTTON, LEFT_STICK, RIGHT_STICK, INVALID };
enum class DstState { NoPress, PressStart, QuickSoftTap, QuickFullPress, QuickFullRelease, SoftPress, DelayFullPress, PressStartResp, INVALID };
enum class BtnState {
	NoPress, BtnPress, TapRelease, WaitSim, SimPress, SimRelease,
	DblPressStart, DblPressNoPressTap, DblPressNoPressHold, DblPressPress, INVALID
};
enum class BtnEvent { OnPress, OnTap, OnHold, OnTurbo, OnRelease, OnTapRelease, OnHoldRelease, INVALID };
enum class Switch : char { OFF, ON, INVALID, }; // Used to parse autoload assignment

// Workaround default string streaming operator
class PathString : public string // Should be wstring
{
public:
	PathString() = default;
	PathString(in_string path)
		: string(path)
	{}
};

// Needs to be accessed publicly
extern WORD nameToKey(const std::string& name);

struct KeyCode
{
	static const KeyCode EMPTY;

	WORD code;
	string name;

	inline KeyCode()
		: code(0)
		, name()
	{}

	inline KeyCode(in_string keyName)
		: code(nameToKey(keyName))
		, name(code != 0 ? keyName : string())
	{}

	inline operator bool()
	{
		return code != 0;
	}

	inline bool operator ==(const KeyCode& rhs)
	{
		return code == rhs.code && name == rhs.name;
	}

	inline bool operator !=(const KeyCode& rhs)
	{
		return !operator=(rhs);
	}
};

// Used for XY pair values such as sensitivity or GyroSample
// that includes a nicer accessor
struct FloatXY : public pair<float, float>
{
	FloatXY(float x = 0, float y = 0)
		: pair(x, y)
	{}

	inline float x() {
		return first;
	}

	inline float y() {
		return second;
	}

};

// Set of gyro control settings bundled in one structure
struct GyroSettings {
	bool always_off = false;
	ButtonID button = ButtonID::NONE;
	GyroIgnoreMode ignore_mode = GyroIgnoreMode::BUTTON;

	GyroSettings() = default;
	// This constructor is required to make use of the default value of JSMVariable's constructor
	GyroSettings(int dummy) : GyroSettings() {}
};


class DigitalButton;

typedef function<void(DigitalButton *)> OnEventAction;

// This structure handles the mapping of a button, buy processing and action
// to be done on tap, hold, turbo and others. It holds a map of actions to perform
// when a specific event happens. This replaces the old Mapping structure.
class Mapping
{
public:
	enum class ActionModifier { None, Toggle, Instant, INVALID};
	enum class EventModifier { None, StartPress, ReleasePress, TurboPress, TapPress, HoldPress, INVALID };

	// Identifies having no binding mapped
	static const Mapping NO_MAPPING;

private:
	map<BtnEvent, OnEventAction> eventMapping;
	float tapDurationMs = MAGIC_TAP_DURATION;
	string representation;

	void InsertEventMapping(BtnEvent evt, OnEventAction action);
	static void RunAllActions(DigitalButton *btn, int numEventActions, ...);

public:
	Mapping() = default;

	Mapping(in_string mapping);

	Mapping(int dummy) : Mapping() {}

	void ProcessEvent(BtnEvent evt, DigitalButton &button, in_string displayName) const;

	bool AddMapping(KeyCode key, EventModifier evtMod, ActionModifier actMod = ActionModifier::None);

	inline void setRepresentation(in_string rep)
	{
		representation = rep;
	}

	inline bool isValid() const
	{
		return !eventMapping.empty();
	}

	inline string toString() const
	{
		return representation;
	}

	inline float getTapDuration() const
	{
		return tapDurationMs;
	}

	inline void clear()
	{
		eventMapping.clear();
		representation.clear();
		tapDurationMs = MAGIC_TAP_DURATION;
	}
};

// This function is defined in main.cpp. It enables two sim press variables to
// listen to each other and make sure they both hold the same values.
void SimPressCrossUpdate(ButtonID sim, ButtonID origin, Mapping newVal);

// This operator enables reading any enum from string
template <class E, class = std::enable_if_t < std::is_enum<E>{} >>
istream &operator >>(istream &in, E &rhv)
{
	string s;
	in >> s;
	auto opt = magic_enum::enum_cast<E>(s);
	rhv = opt ? *opt : *magic_enum::enum_cast<E>("INVALID");
	return in;
}

// This operator enables writing any enum to string
template <class E, class = std::enable_if_t < std::is_enum<E>{} >>
ostream &operator <<(ostream &out, E rhv)
{
	out << magic_enum::enum_name(rhv);
	return out;
}

// The following operators enable reading and writing JSM's custom
// types to and from string, or handles exceptions
istream & operator >> (istream &in, ButtonID &rhv);
ostream &operator << (ostream &out, ButtonID rhv);

istream &operator >>(istream &in, FlickSnapMode &fsm);
ostream &operator <<(ostream &out, FlickSnapMode fsm);

istream &operator >>(istream &in, GyroSettings &gyro_settings);
ostream &operator <<(ostream &out, GyroSettings gyro_settings);
bool operator ==(const GyroSettings &lhs, const GyroSettings &rhs);
inline bool operator !=(const GyroSettings &lhs, const GyroSettings &rhs)
{
	return !(lhs == rhs);
}

istream &operator >> (istream &in, Mapping &mapping);
ostream &operator << (ostream &out, Mapping mapping);
bool operator ==(const Mapping &lhs, const Mapping &rhs);
inline bool operator !=(const Mapping &lhs, const Mapping &rhs)
{
	return !(lhs == rhs);
}

ostream &operator << (ostream &out, FloatXY fxy);
istream &operator >> (istream &in, FloatXY &fxy);
bool operator ==(const FloatXY &lhs, const FloatXY &rhs);
inline bool operator !=(const FloatXY &lhs, const FloatXY &rhs)
{
	return !(lhs == rhs);
}

istream& operator >> (istream& in, AxisMode& am);
// AxisMode can use the templated operator for writing

istream& operator >> (istream& in, PathString& fxy);
