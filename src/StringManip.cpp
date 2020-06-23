#include "pch.h"
#include "StringManip.h"

string stringToUpper(string myString)
{
	auto out = myString;

	for (uint i = 0; i < out.length(); ++i)
		out[i] = toupper(out[i]);

	return out;
}

vector<string> stringSplit(string data, string token)
{
	vector<string> output;
	auto pos = string::npos;

	do
	{
		pos = data.find(token);
		output.push_back(data.substr(0, pos));

		if (string::npos != pos)
			data = data.substr(pos + token.size());

	} while (string::npos != pos);

	return output;
}

string GetFileName(string &input)
{
	string sep("/");
	size_t pos = input.find_last_of(sep);

	if (pos != string::npos)
	{
		return input.substr(pos + 1);
	}

	else
		return input;
}

string RemoveSuffix(string &input)
{
	string sep(".");
	uint pos = uint(input.find_last_of(sep));

	if (pos != string::npos)
	{
		return input.substr(0, pos);
	}

	else
		return input;
}

