#include "Randomizer.h"
#include <iostream>
#include <array>
#include <string>
Randomizer random(0, 9);

std::string genPart()
{
	/*generate 4 random numbers*/
	return std::to_string(random.getRandomValue()) + std::to_string(random.getRandomValue()) + std::to_string(random.getRandomValue()) + std::to_string(random.getRandomValue());
}
void genKey(std::array<std::string, 4>& arr)
{
	/*fill all blocks randomly*/
	for (auto& el : arr)
		el = genPart();
}
void sum(std::array<std::string, 4>& blockArray, std::array<std::int32_t, 4>& blockCheckSum)
{
	for (size_t i = 0; i < blockArray.size(); ++i)/*get sum for each block*/
		blockCheckSum.at(i) = blockArray.at(i).at(0) + blockArray.at(i).at(1) + blockArray.at(i).at(2) + 4 * blockArray.at(i).at(3) - 336;
}
bool compareBlockAnyPos(std::array<std::string, 4>& blockArray, uint32_t pos)
{
	/*check unique number on each place*/
	if (blockArray.at(0).at(pos) == blockArray.at(1).at(pos) ||
		blockArray.at(1).at(pos) == blockArray.at(2).at(pos) ||
		blockArray.at(2).at(pos) == blockArray.at(3).at(pos))
		return true;
	return false;
}
bool checkKey(std::array<std::string, 4>& blockArray,std::array<std::int32_t, 4>& blockCheckSum)
{
	sum(blockArray, blockCheckSum);//fill each blocks sum
	int32_t sum=0;
	for (auto& el : blockCheckSum)
		sum += el;//make result sum
	sum = sum >> 2;//and div it on 4
	for (auto& el : blockCheckSum)
		if (sum != el)//all blocks sum should be equal
			return false;
	for (size_t i = 0; i < blockArray.front().size(); ++i)
		if (compareBlockAnyPos(blockArray, i))//check each position
			return false;
	return true;
}
void main(void)
{
	std::array<std::string, 4> blockArray{ "0000","0000","0000","0000" };//blocks buffer
	std::array<std::int32_t, 4> blockCheckSum{ 0, 0, 0, 0 };//buffer of blocks sum
	while (true)
	{
		genKey(blockArray);//generate new key
		if (checkKey(blockArray, blockCheckSum))//if succeed  - print it
		{
			std::string result = "Code is - ";
			for (auto& el : blockArray)
				result += el + '-';
			std::cout << result.substr(0, result.size() - 1) << std::endl;
			system("pause");
			return;
		}
	}
}