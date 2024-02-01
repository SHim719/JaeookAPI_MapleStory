#pragma once

#include "framework.h"
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <assert.h>
#include <functional>
#include <bitset>
#include <unordered_map>
#include <format>


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

#define SAFE_ARR_DELETE(p) if (p) {delete[] p; p = nullptr; }
#define PURE = 0

using std::vector;
using std::list;
using std::for_each;
using std::string;
using std::wstring;
using std::map;
using std::function;
using std::move;
using std::clamp;
using std::bitset;
using std::unordered_map;
using std::min;
using std::max;
using std::swap;
using std::to_string;
using std::to_wstring;
using std::bind;
using std::format;
using std::pair;
using std::abs;
using std::fabs;

#include "Vec2.h"
#include "Enums.h"

struct Timer
{
	float m_fNowTime = 0.f;
};

int generateRandomNumber(int firstDigit, int totalDigits)
{
    // �� ���ڸ����� 1 �̻� 9 ������ �������� �մϴ�.
    if (firstDigit < 1 || firstDigit > 9) {
        throw std::invalid_argument("�� ���ڸ����� 1 �̻� 9 ������ �������� �մϴ�.");
    }

    // �� �ڸ����� 1 �̻��̾�� �մϴ�.
    if (totalDigits < 1) {
        throw std::invalid_argument("�� �ڸ����� 1 �̻��̾�� �մϴ�.");
    }

    // �� ���ڸ����� ������ ������ �ڸ����� �����ϰ� ����
    int randomNumber = firstDigit * (int)pow(10, totalDigits - 1) + rand() % (int)pow(10, totalDigits - 1);

    return randomNumber;
}

bool Calc_Critical()
{
    if (rand() % 10 < 2)
        return true;
    else
        return false;
}