#include "C07PacketPlayerDigging.h"

C07PacketPlayerDigging C07PacketPlayerDigging::new_object(int action, int block_x, int block_y, int block_z, int side, JNIEnv* env)
{
	return C07PacketPlayerDigging
	(
		env->NewObject
		(
			C07PacketPlayerDiggingClass.get_jclass(env), C07PacketPlayerDiggingClass.getMethodID("<init>"),
			action,
			block_x,
			block_y,
			block_z,
			side
		),
		env
	);
}
