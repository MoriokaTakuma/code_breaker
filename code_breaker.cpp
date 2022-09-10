#include<stdio.h>
#include <random>
#include <time.h>
#include <ctype.h>

#define NUM_DIGIT 4


/***************************
 * 入力された文字が全て数字であるかを判断する
 * input[in]:入力された文字が格納された配列
 * len[in]:文字数
 * 返却値：1（全ての文字が数字である場合）
 *      ：0（それ以外）
 * *************************/
int is_allDigit(char input_str[], int len) {
	for (int i = 0; i < len; i++) {
		if (!isdigit(input_str[i])) {
			return 0;
		}
	}
	return 1;
}
/***************************
* 入力された文字が重複していないかを判断する
* input_str[in]:入力された文字が格納された配列
* len[in]:文字数
* 返却値：1（全ての文字が重複していない場合）
*      ：0（それ以外）
* *************************/
int is_allDifferent(char input_str[], int len) {
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (input_str[i] == input_str[j]) {
				return 0;
			}
		}
	}
	return 1;
}

void inputNum(char input[], int num_digit) {
	char input_str[256];

	while (1) {
		printf("%d桁の数字を入力してください:", num_digit);
		scanf_s("%s", input_str);

		if (strlen(input_str) != num_digit) {
			printf("%d桁じゃないです...\n", num_digit);
			continue;
		}

		if (!is_allDigit(input_str, num_digit)) {
			printf("数字以外が入力されてます...\n");
			continue;
		}

		if (!is_allDifferent(input_str, num_digit)) {
			printf("同じ数字が入力されてます...\n");
			continue;
		}


		for (int i = 0; i < num_digit; i++) {
			input[i] = input_str[i];
		}

		break;
	}
}
/***************************
 * Hit数を数える
 * input[in]:入力された数が格納された配列
 * answer[in]:正解の数が格納された配列
 * num_digit[in]:数の桁数
 * 返却値：Hit数
 * *************************/
int countHit(char input[], char answer[], int num_digit) {
	int num_hit = 0;

	for (int i = 0; i < num_digit; i++) {
		for (int j = 0; j < num_digit; j++) {
			if (answer[i] == input[j]) {
				if (i == j) {
					num_hit++;
				}
			}
		}
	}

	return num_hit;
}

/***************************
 * Blow数を数える
 * input[in]:入力された数が格納された配列
 * answer[in]:正解の数が格納された配列
 * num_digit[in]:数の桁数
 * 返却値：Blow数
 * *************************/
int countBlow(char input[], char answer[], int num_digit) {

	int num_blow = 0;

	for (int i = 0; i < num_digit; i++) {
		for (int j = 0; j < num_digit; j++) {
			if (answer[i] == input[j]) {
				if (i != j) {
					num_blow++;
				}
			}
		}
	}

	return num_blow;
}


void randNum(int array[], int size)
{
    int i, j;
	int tmp;

	//範囲の末尾を設定
	i = size - 1;

	//範囲(0 ～ i)からランダムに１つデータを選ぶ
	while (i > 0)
	{
		j = rand() % (i + 1);

		// ランダムに決めたデータと範囲の末尾のデータを交換 
		tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;

		//範囲を狭める 
		i--;
	}
}

int main()
{
	// ランダムな値を利用する為の準備
	srand(time(NULL));

	//int array[9];
	char answer[NUM_DIGIT];
	int num_hit, num_blow;

	// 乱数の範囲は1〜9 
	/*for (int i = 0; i < 9; i++) 
	{
		array[i] = i + 1;
	}*/

	/* 1.正解を用意する */
	char nums[] = {
		'0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9'
	};
	int num_num = sizeof(nums) / sizeof(nums[0]);

	//arrayの中身をシャッフル 
	//randNum(nums, sizeof(array) / sizeof(array[0]));

	for (int i = 0; i < NUM_DIGIT; i++)
	{
		// 重複なしの乱数を生成（取得）
		answer[i] = nums[i];
	}
	
	do {
		/* 2.プレイヤーの入力を受け付ける */
		char input[4];
		inputNum(input, NUM_DIGIT);

		/* 3.Hit数とBlow数を表示する */
		num_hit = countHit(answer, input, NUM_DIGIT);
		num_blow = countBlow(answer, input, NUM_DIGIT);
		printf("%d HIT!! / %d BLOW!!\n", num_hit, num_blow);

	} while (num_hit < NUM_DIGIT); /* 4.ゲームクリアかどうか判断する */
	return 0;
	
}


