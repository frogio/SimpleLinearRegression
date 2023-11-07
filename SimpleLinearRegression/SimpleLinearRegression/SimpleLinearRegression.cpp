#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

#define STUDENT_COUNT 30

struct studentBuild {
	double height;
	double weight;
};

struct Model {
	double coeff;
	double y_section;
};

void MakeRandomData(struct studentBuild * s, int studentCount);
void ShowData(struct studentBuild* s, int studentCount);
struct studentBuild GetMean(struct studentBuild* s, int studentCount);
void TranslateDataToMean(struct studentBuild* s, struct studentBuild mean, int studentCount);

Model MakeModel(struct studentBuild* s, int studentCount, struct studentBuild mean);
double GetCoefficient(struct studentBuild* s, int studentCount);

void Predict(Model* model);

void main() {

	struct studentBuild students[STUDENT_COUNT] = { 0, };
	struct studentBuild mean;

	printf("make random data of student build...\n\n");
	
	MakeRandomData(students, STUDENT_COUNT);
	ShowData(students, STUDENT_COUNT);

	mean = GetMean(students, STUDENT_COUNT);
	
	printf("\nmean data of student build...\n\n");

	ShowData(&mean, 1);

	printf("\ntranslated data of student build...\n\n");

	TranslateDataToMean(students, mean, STUDENT_COUNT);
	ShowData(students, STUDENT_COUNT);

	Model model = MakeModel(students, STUDENT_COUNT, mean);

	printf("\ncompleted model is...\n");
	printf("Y = %lfx + %lf", model.coeff, model.y_section);

	printf("\n\n");

	Predict(&model);

}

void MakeRandomData(struct studentBuild* s, int studentCount) {

	// 데이터에 Trend를 내포하고 있어야 한다.
	// ex) 키가 큰 아이는 더 무거울 것이다.와 같은 경향성...
	
	srand((unsigned)time(NULL));

	for (int i = 0; i < studentCount; i++) {
		s[i].height = rand() % 20 + ((rand() % 10) / 10.0) + 165;

		// 데이터의 경향성을 주기 위해 신장 별로 몸무게를 다른 기준으로 준다.
		if(s[i].height > 178)
			s[i].weight = rand() % 10 + ((rand() % 10) / 10.0) + 75;

		else if(s[i].height > 170)
			s[i].weight = rand() % 7 + ((rand() % 10) / 10.0) + 65;

		else if (s[i].height > 165)
			s[i].weight = rand() % 5 + ((rand() % 10) / 10.0) + 55;

		else if (s[i].height > 160)
			s[i].weight = rand() % 3 + ((rand() % 10) / 10.0) + 50;

	}


}

void ShowData(struct studentBuild* s, int studentCount) {
	
	for (int i = 0; i < studentCount; i++)
		printf("%02d. Weight : %lf Height : %lf\n", i + 1, s[i].weight, s[i].height);

}

struct studentBuild GetMean(struct studentBuild* s, int studentCount) {

	struct studentBuild mean = {0, };
	for (int i = 0; i < studentCount; i++) {
		mean.height += s[i].height;
		mean.weight += s[i].weight;
	}

	mean.height /= studentCount;
	mean.weight /= studentCount;

	return mean;
}

void TranslateDataToMean(struct studentBuild* s, struct studentBuild mean, int studentCount) {

	for (int i = 0; i < studentCount; i++) {
		s[i].weight -= mean.weight;
		s[i].height -= mean.height;
	}

}


Model MakeModel(struct studentBuild* s, int studentCount, struct studentBuild mean) {

	Model model;
	
	model.coeff = GetCoefficient(s, studentCount);
	model.y_section = -model.coeff * mean.height + mean.weight;

	return model;
}

double GetCoefficient(struct studentBuild* s, int studentCount){
	
	double xy = 0, 
		square_x = 0;
	
	for (int i = 0; i < studentCount; i++) {
		xy += s[i].weight * s[i].height;
		square_x += s[i].height * s[i].height;
	
	}

	return xy / square_x;

}

void Predict(Model* model) {

	double height = 0;

	while (1) {
	
		printf("enter height to want to predict weight : ");
		scanf("%lf", &height);

		double predict_result = height * model->coeff + model->y_section;
		printf("weight of what you enter is %lf\n\n", predict_result);
	
	}


}