#include "APPengine.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include <fstream>
#include <iostream>


//seting base variables so there wont be any magical numers
MyString beginningofafile = "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg>\n";
MyString endingofafile = "</svg>";
const int baseshapescapp = 5;
const int basenumberofshapes = 0;
const int baselinelength = 1000;
const int baseshapescapmultiplier = 2;

APPengine::APPengine()
{
	//set the base parameters
	numberofshapes = basenumberofshapes;
	shapescap = baseshapescapp;
	shapes = new Shape * [shapescap];
}
APPengine::~APPengine()
{
	//erace the dinamic memmory
	freememory();
}
void APPengine::Run()
{
	MyString* tokens=nullptr;
	int tokenscount = 0;
	char chArr[baselinelength];
	//take the input
	std::cin.getline(chArr, baselinelength);
	MyString  token(chArr);
	//check if the command is not the exit command
	while (!(token=="Exit") && !(token == "exit"))
	{
		//split the input by whitespace
		split(tokens, token.GetValue(), tokenscount, " ");
		//execute the corresponding command
		if (tokens[0] == "Print" || tokens[0] == "print")
		{
			print();
		}
		else if (tokens[0] == "Open" || tokens[0] == "open")
		{
			takefromfile(tokens, tokenscount);
		}
		else if (tokens[0] == "Save" || tokens[0] == "save")
		{
			savetofile(tokens, tokenscount);
		}
		else if (tokens[0] == "Within" || tokens[0] == "within")
		{
			Within(tokens, tokenscount);
		}
		else if (tokens[0] == "Create" || tokens[0]=="create")
		{
			Create(tokens,tokenscount);
		}
		else if (tokens[0] == "Erace"|| tokens[0] == "erace")
		{
			Erase(tokens, tokenscount);
		}
		else if (tokens[0] == "Translate" || tokens[0] == "translate")
		{
			translate(tokens, tokenscount);
		}
		else if (tokens[0] == "PointIn" || tokens[0] == "pointin")
		{
			PointIn(tokens, tokenscount);
		}
		else if (tokens[0] == "Areas" || tokens[0] == "areas")
		{
			Areas();
		}
		else if (tokens[0] == "Pers" || tokens[0] == "pers")
		{
			Pers();
		}
		else
		{
			//display this message if the comman is not suported
			std::cout << "Incorrect input." << std::endl;
		}
		//take the input again
		std::cin.getline(chArr, baselinelength);
		token=chArr;
		//free the memory from the MyString array
		delete[] tokens;
	}
}
void APPengine::freememory()
{
	for (int i = 0; i < numberofshapes; i++)
	{
		//free the memory from the given pointer
		delete shapes[i];
	}
	//delete the pointer array
	delete[] shapes;
}
void APPengine::print() const
{
	for (int i = 0; i < numberofshapes; i++)
	{
		//print the corresponding index and the shape
		std::cout << i+1 << ". ";
		shapes[i]->Print();
	}
	if (numberofshapes == 0)
	{
		//display this message if there are no shapes
		std::cout << "Thera are no shapes" << std::endl;
	}
}
void APPengine::Create(MyString* tokens, const int tcount)
{
	MyString shape = tokens[1];
	if (shape == "circle")
	{
		//create a default circle and set it's parameters if possible
		Circle C;
		MyString prop;
		//check if parameters like x or y are given
		if (tcount >= 3)
		{
			prop = tokens[2];
			C.SetX(stringToInt(prop.GetValue()));
		}
		
		if (tcount >= 4)
		{
			prop = tokens[3];
			C.SetY(stringToInt(prop.GetValue()));
		}
		
		if (tcount >= 5)
		{
			prop = tokens[4];
			C.SetRadius(stringToInt(prop.GetValue()));
		}
		
		if (tcount >= 6)
		{
			prop = tokens[5];
			C.SetFill(prop);
		}
		//add the shape to the arrray
		AddCircle(C);
		std::cout << "Successfully created circle(" << numberofshapes << ")" << std::endl;
	}
	else if (shape == "line")
	{
		//create a default line and set it's parameters if possible
		Line L;
		MyString prop;
		//check if parameters like x or y are given
		if (tcount >= 3)
		{
			prop = tokens[2];
			L.SetX(stringToInt(prop.GetValue()));
		}

		if (tcount >= 4)
		{
			prop = tokens[3];
			L.SetY(stringToInt(prop.GetValue()));
		}

		if (tcount >= 5)
		{
			prop = tokens[4];
			L.SetX2(stringToInt(prop.GetValue()));
		}
		if (tcount >= 6)
		{
			prop = tokens[5];
			L.SetY2(stringToInt(prop.GetValue()));
		}
		if (tcount >= 7)
		{
			prop = tokens[6];
			L.SetFill(prop);
		}
		//add the shape to the array
		AddLine(L);
		std::cout << "Successfully created line(" << numberofshapes << ")" << std::endl;
	}
	else if (shape == "rectangle")
	{
		//create a default rectangle and set it's parameters if possible
		Rectangle R;
		MyString prop;
		//check if parameters like x or y are given
		if (tcount >= 3)
		{
			prop = tokens[2];
			R.SetX(stringToInt(prop.GetValue()));
		}

		if (tcount >= 4)
		{
			prop = tokens[3];
			R.SetY(stringToInt(prop.GetValue()));
		}

		if (tcount >= 5)
		{
			prop = tokens[4];
			R.SetWidth(stringToInt(prop.GetValue()));
		}
		if (tcount >= 6)
		{
			prop = tokens[5];
			R.SetHeight(stringToInt(prop.GetValue()));
		}

		if (tcount >= 7)
		{
			prop = tokens[6];
			R.SetFill(prop);
		}
		//add the shape to the array;
		AddRectangle(R);
		std::cout << "Successfully created rectangle(" << numberofshapes << ")" << std::endl;
	}
	else
	{
		//display this messsge if the given shape is not supported
		std::cout << "shape can not be " << shape.GetValue() << std::endl;
	}
}
void APPengine::Erase(MyString* tokens, const int tcount)
{
	//check if an index is givven
	if (tcount >= 2)
	{
		int index = stringToInt(tokens[1].GetValue());
		int modindex = index - 1;
		//check if the index is valid
		if (modindex < 0 || modindex >= numberofshapes)
		{
			//display this message if it is
			std::cout << "There is no figure number " << index << "!" << std::endl;
		}
		else
		{
			//erace the element at the given index
			std::cout << "Erased a " << shapes[modindex]->GetType() << "(" << index << ")" << std::endl;
			delete shapes[modindex];
			//shift the elements by one
			for (int i = modindex; i < numberofshapes - 1; i++)
			{
				shapes[i] = shapes[i + 1];
			}
			shapes[--numberofshapes] = nullptr;
		}
	}
	else
	{
		//erace all elements
		for (int i = 0; i < numberofshapes; i++)
		{
			delete[] shapes[i];
		}
		numberofshapes = basenumberofshapes;
		std::cout << "Eraced all shapes" << std::endl;
	}
	
}
void APPengine::Within(MyString* tokens, const int tcount)const
{
	MyString shape = tokens[1];
	//check the type of the figure in which the figures are supposed to reside
	if (shape == "circle")
	{
		if (tcount >= 5)
		{
			//get values for the circle
			int X = stringToInt(tokens[2].GetValue());
			int Y = stringToInt(tokens[3].GetValue());
			int R = stringToInt(tokens[4].GetValue());
			bool hasfig = false;
			//go through all the figures and print the ones tht are within
			for (int i = 0; i < numberofshapes; i++)
			{
				if (shapes[i]->WithinCircle(X, Y, R))
				{
					hasfig = true;
					std::cout << i +1<< ". ";
					shapes[i]->Print();
				}
			}
			if (!hasfig)
			{
				//display this message if there are no figure within this circle
				std::cout << "No figures are located within circle " << X << " " << Y << " " << R << std::endl;
			}
		}
		else
		{
			//display this message if the user has not inputerd x, y and radius for the circle
			std::cout << "Insufficient parameters" << std::endl;
		}
	}
	else if (shape == "rectangle")
	{
		if (tcount >= 6)
		{
			//get values for the rectangle
			int X = stringToInt(tokens[2].GetValue());
			int Y = stringToInt(tokens[3].GetValue());
			int W = stringToInt(tokens[4].GetValue());
			int H = stringToInt(tokens[4].GetValue());
			bool hasfig = false;
			//go through all the figures and print the ones tht are within
			for (int i = 0; i < numberofshapes; i++)
			{
				if (shapes[i]->WithinRect(X,Y,W,H))
				{
					hasfig = true;
					std::cout << i +1<< ". ";
					shapes[i]->Print();
				}
			}
			if (!hasfig)
			{
				//display this message if there are no figure within this rectangle
				std::cout << "No figures are located within rectangle " << X << " " << Y << " " << W << " " << H << std::endl;
			}
		}
		else
		{
			//display this message if the user has not inputerd x, y, width and heigth for the rectangle
			std::cout << "Insufficient parameters" << std::endl;
		}
	}
	else
	{
		std::cout << "Shape can not be " << shape.GetValue() << std::endl;
	}
}
void APPengine::PointIn(MyString* tokens, const int tcount)const
{
	//che if parameters for the point are given
	if (tcount >= 3)
	{
		int X = stringToInt(tokens[1].GetValue());
		int Y = stringToInt(tokens[2].GetValue());
		bool hasel = false;
		//iterate through the shapes and thisplay thise in which the point resides
		for (int i = 0; i < numberofshapes; i++)
		{
			if (shapes[i]->PointIn(X,Y))
			{
				hasel = true;
				std::cout << i+1 << ". ";
				shapes[i]->Print();
			}
		}
		if (!hasel)
		{
			//display this message if the point isn't in any of the shapes
			std::cout << "There rea no shapes in which the point is contained" << std::endl;
		}
	}
	else
	{
		//if parameters for the point are not given dispaly this message
		std::cout << "Insufficient parameters" << std::endl;
	}
}
void APPengine::Areas()const
{
	//go through the shapes and print their type and area 
	for (int i = 0; i < numberofshapes; i++)
	{
		std::cout << i+1 << "-" << shapes[i]->GetType() << ": " << shapes[i]->GetArea() << std::endl;
	}
}
void APPengine::Pers()const
{
	//go through the shapes and print their type and perimeter
	for (int i = 0; i < numberofshapes; i++)
	{
		std::cout << i+1 << "-" << shapes[i]->GetType() << ": " << shapes[i]->GetPerimeter() << std::endl;
	}
}
void APPengine::takefromfile(MyString* tokens, const int tcount)
{
	//check if a filepath is givven
	if (tcount >= 2)
	{
		//set the new filepath
		currentfilepath = tokens[1];
	}
	if (!(currentfilepath == ""))
	{
		//open a filestream
		std::ifstream ifile;
		ifile.open(currentfilepath.GetValue());
		if (!ifile.is_open())
		{
			//display this message if the file can no load
			std::cout << "Could not oppen file" << std::endl;
		}
		else
		{
			MyString text;
			char line[baselinelength];
			//store all text from the file in one string
			while (!ifile.eof())
			{
				ifile.getline(line, 1000);
				text += line;
				text += "\n";
			}
			MyString* inptokens = nullptr;
			int numberofinptokens = 0;
			//split the text from the file by ' ', '\n' and '/'
			split(inptokens, text.GetValue(), numberofinptokens," \n/");
			//go through the code segments
			for (int i = 0; i < numberofinptokens; i++)
			{
				//check if the given code segment begins a new shape
				if (inptokens[i] == "<rect")
				{
					//create a rectangle
					Rectangle R;
					for (; i < numberofinptokens && inptokens[i].indexof('>') == -1; i++)
					{
						//check if the current code segment contains '=' which means tht it sets a value
						if (inptokens[i].indexof('=') != -1)
						{
							int indeq = inptokens[i].indexof('=');
							//take the text before and after the '='
							MyString key = inptokens[i].substring(0, indeq);
							MyString val= inptokens[i].substring(indeq+2, chArlen(inptokens[i].GetValue())-1);
							//check if th key corresponds to the properties of the rectangle if so set the propertie to the val
							if (key == "x")
							{
								R.SetX(stringToInt(val.GetValue()));
							}
							else if( key=="y")
							{
								R.SetY(stringToInt(val.GetValue()));
							}
							else if (key == "width")
							{
								R.SetWidth(stringToInt(val.GetValue()));
							}
							else if (key == "height")
							{
								R.SetHeight(stringToInt(val.GetValue()));
							}
							else if (key == "fill")
							{
								R.SetFill(val);
							}
						}
					}
					AddRectangle(R);
				}
				else if (inptokens[i] == "<circle")
				{
					//do the same with the circle
					Circle C;
					for (; i < numberofinptokens && inptokens[i].indexof('>') == -1; i++)
					{
						if (inptokens[i].indexof('=') != -1)
						{
							int indeq = inptokens[i].indexof('=');
							MyString key = inptokens[i].substring(0, indeq);
							MyString val = inptokens[i].substring(indeq + 2, chArlen(inptokens[i].GetValue()) - 1);
							if (key == "cx")
							{
								C.SetX(stringToInt(val.GetValue()));
							}
							else if (key == "cy")
							{
								C.SetY(stringToInt(val.GetValue()));
							}
							else if (key == "r")
							{
								C.SetRadius(stringToInt(val.GetValue()));
							}
							else if (key == "fill")
							{
								C.SetFill(val);
							}
						}
					}
					AddCircle(C);
				}
				else if (inptokens[i] == "<line")
				{
					//do the same with the line
					Line L;
					for (; i < numberofinptokens && inptokens[i].indexof('>') == -1; i++)
					{
						if (inptokens[i].indexof('=') != -1)
						{
							int indeq = inptokens[i].indexof('=');
							MyString key = inptokens[i].substring(0, indeq);
							MyString val = inptokens[i].substring(indeq + 2, chArlen(inptokens[i].GetValue()) - 1);
							if (key == "x1")
							{
								L.SetX(stringToInt(val.GetValue()));
							}
							else if (key == "y1")
							{
								L.SetY(stringToInt(val.GetValue()));
							}
							else if (key == "x2")
							{
								L.SetX2(stringToInt(val.GetValue()));
							}
							else if (key == "y2")
							{
								L.SetY2(stringToInt(val.GetValue()));
							}
							else if (key == "fill")
							{
								L.SetFill(val);
							}
						}
					}
					AddLine(L);
				}
			}
			//display this message if the file is successfuly oppeened
			std::cout << "Successfully opened " << currentfilepath.GetValue() << std::endl;
			delete[] inptokens;

		}
		//close the file
		ifile.close();
	}
	else
	{
		//display this message if a filepath is not given
		std::cout << "No file path has been selected" << std::endl;
	}
}
void APPengine::savetofile(MyString* tokens, const int tcount)
{
	//check if a file path is given
	if (tcount >= 2)
	{
		//if so set the current filepath to the new one
		currentfilepath = tokens[1];
	}
	if (!(currentfilepath == ""))
	{
		//open a filestream
		std::ofstream ofile;
		//check if the stream opens
		ofile.open(currentfilepath.GetValue());
		if (!ofile.is_open())
		{
			//display this massage if the file cant be oppened
			std::cout << "Could not oppen file" << std::endl;
		}
		else
		{
			//write the begining of a file
			ofile << beginningofafile.GetValue();
			for (int i = 0; i < numberofshapes; i++)
			{
				//write the corresponding shape in the file
				shapes[i]->svgel(ofile);
			}
			//writhe the ending of a file
			ofile << endingofafile.GetValue();
			ofile.close();
		}
		//display this message if the date was collected successfuli
		std::cout << "sucessfully saved in " << currentfilepath.GetValue() << std::endl;
	}
	else
	{
		//display this message if a there isnt a filepath
		std::cout << "No file path has been selected" << std::endl;
	}

}
void APPengine::AddLine(const Line& L)
{
	//check if there is enough space
	if (numberofshapes >= shapescap)
	{
		//if not resize the array
		resize();
	}
	//clone the line and add it to the array
	shapes[numberofshapes++] = L.clone();
}
void APPengine::AddCircle(const Circle &C)
{
	//check if there is enough space
	if (numberofshapes >= shapescap)
	{
		//if not resize the array
		resize();
	}
	//clone the circle and add it to the array
	shapes[numberofshapes++] = C.clone();
}
void APPengine::AddRectangle(const Rectangle & R)
{
	//check if there is enough space
	if (numberofshapes >= shapescap)
	{
		//if not resize the array
		resize();
	}
	//clone the rectangle and add it to the array
	shapes[numberofshapes++] = R.clone();
}
void APPengine::resize()
{
	shapescap *= baseshapescapmultiplier;
	//create a new array with a larger size
	Shape** tempshapes = new Shape * [shapescap];
	for (int i = 0; i < numberofshapes; i++)
	{
		//save the values from the previous array to the new one
		tempshapes[i] = shapes[i];
		shapes[i] = nullptr;
	}
	//delete the previous array
	delete[] shapes;
	//set the value of the base arrray to the value of the new array
	shapes = tempshapes;
	tempshapes = nullptr;
}
void APPengine::translate(MyString* tokens, const int tcount)
{
	//!!! this function works by inputing "translate y x" and not "translate vertical=y horizonatl=x" where x an y are numbers
	//if you want to translate a single element input "translate y x ind" whre ind is a number and is the index of the element you want to translate
	//check if enough parameters are given
	if (tcount >= 3)
	{
		//get x and y
		int Y = stringToInt(tokens[1].GetValue());
		int X = stringToInt(tokens[2].GetValue());
		if (tcount >= 4)
		{
			//get index
			int ind=stringToInt(tokens[3].GetValue())-1;
			if (ind >= 0 && ind < numberofshapes)
			{
				//translate the corresponding shape
				shapes[ind]->translate(Y, X);
				std::cout << "Translated " << shapes[ind]->GetType() << "(" << ind + 1 << ")" << std::endl;
			}
			else
			{
				//display this message if the index is incorrect
				std::cout << "there is no element of index " << ind + 1 << std::endl;
			}
			
		}
		else
		{
			for (int i = 0; i < numberofshapes; i++)
			{
				//translate the shapes
				shapes[i]->translate(Y, X);
			}
			//display this message if all shapes have been translated
			std::cout << "Translated all shapes" << std::endl;
		}
	}
	else
	{
		//display this message if x and y are not given
		std::cout << "Insufficient parameters" << std::endl;
	}
}