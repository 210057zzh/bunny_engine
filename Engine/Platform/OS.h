#pragma once
#include <unordered_map>

class OS {
public:
	struct OsKeyBoardEvent {
		enum class Type {
			Keyup,
			Keydown,
			Invalid
		};

		Type type = Type::Invalid;
		uint32_t code = -1;
	};

	struct OsMouseEvent {
		enum class Type {
		};
	};

	OS() = default;
	virtual ~OS() = default;
	virtual void SetResolution(int width, int height) = 0;
	virtual void InitializeWindow() = 0;
	virtual int Loop() = 0;
	virtual void ProcessMessage() = 0;

	OS(const OS &os) = delete;
	OS(OS &&os) = delete;
	OS &operator=(const OS &os) = delete;
	OS &operator=(OS &&os) = delete;
};
