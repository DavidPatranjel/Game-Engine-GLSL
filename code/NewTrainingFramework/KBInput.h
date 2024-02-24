#pragma once
#include <unordered_map>
class KBInput
{
private:
	enum cameraKeyBind{ MOVE_CAMERA_POSITIVE_X, 
						MOVE_CAMERA_NEGATIVE_X,
						MOVE_CAMERA_POSITIVE_Y,
						MOVE_CAMERA_NEGATIVE_Y,
						MOVE_CAMERA_POSITIVE_Z,
						MOVE_CAMERA_NEGATIVE_Z
	};
	std::unordered_map<std::string, int> inputData = {
			{"MOVE_CAMERA_POSITIVE_X", MOVE_CAMERA_POSITIVE_X},
			{"MOVE_CAMERA_NEGATIVE_X", MOVE_CAMERA_NEGATIVE_X},
			{"MOVE_CAMERA_POSITIVE_Y", MOVE_CAMERA_POSITIVE_Y},
			{"MOVE_CAMERA_NEGATIVE_Y", MOVE_CAMERA_NEGATIVE_Y},
			{"MOVE_CAMERA_POSITIVE_Z", MOVE_CAMERA_POSITIVE_Z},
			{"MOVE_CAMERA_NEGATIVE_Z", MOVE_CAMERA_NEGATIVE_Z},
	};
public:
	char W, A, S, D, Q, E;
	char w, a, s, d, q, e;

	KBInput();
	void BindKey(char key, const std::string& action);
};

