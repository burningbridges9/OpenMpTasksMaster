void PrintResultVector(int cols, int * resVector);
void StaticSchedule(int rows, int * resVector, int cols, int ** matrix, int * vector);

void RuntimeSchedule(int rows, int * resVector, int cols, int ** matrix, int * vector, double endtime, double startTime);

void GuidedSchedule(int rows, int * resVector, int cols, int ** matrix, int * vector, double endtime, double startTime);

void DynamicSchedule(double &startTime, int rows, int * resVector, int cols, int ** matrix, int * vector, double &endtime);
