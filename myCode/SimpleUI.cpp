/*
 * SimpleUI.cpp
 *
 *  Created on: Jan 12, 2026
 *      Author: Admin
 */

#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb &db):db{db}
{
}

// Convert weekday enum to readable string
std::string dayOfWeekToString (const boost::date_time::weekdays& dayOfWeek)
{
	switch (dayOfWeek)
	{
	case boost::date_time::weekdays::Monday:
		return "Monday";
	case boost::date_time::weekdays::Tuesday:
		return "Tuesday";
	case boost::date_time::weekdays::Wednesday:
		return "Wednesday";
	case boost::date_time::weekdays::Thursday:
		return "Thursday";
	case boost::date_time::weekdays::Friday:
		return "Friday";
	case boost::date_time::weekdays::Saturday:
		return "Saturday";
	case boost::date_time::weekdays::Sunday:
		return "Sunday";
	default:
		return "Invalid day";
	}
}
void SimpleUI::addNewCourse()
{
	cout << endl <<"-----------Add New Course---------" << endl;
	cout << "Enter courseKey:";
	unsigned int courseKey;
	cin>>courseKey;

	cout <<"Enter title:";
	string title;
	cin.ignore();
	getline(cin>>ws, title);

	cout <<"Enter major:";
	string major;
	getline(cin>>ws, major);

	cout <<"Enter credit point:";
	float creditPoint;
	cin>>creditPoint;

	cout << "Enter the type of course" << endl
		 << "0-BlockCourse"   << endl
		 << "1-WeeklyCourse" << endl;
	int courseType;
	cin >> courseType;

	//BlockCourse
	if (courseType == 0)
	{
		// Start date
		int day, month, year;
		char dot;
		cout << "Enter the start date (DD.MM.YYYY):" << endl;
		cin >> day>> dot>> month>> dot>> year;
		boost::gregorian::date startDate(year, month, day);

		// End date
		cout << "Enter the end date (DD.MM.YYYY):" << endl;
		cin >> day>> dot>> month>> dot>> year;
		boost::gregorian::date endDate(year, month, day);

		// Start time
		int hour, minute, second = 0;
		char colon;
		cout << "Enter the start time (HH:MM)" << endl;
		cin >> hour>> colon>> minute;
		boost::posix_time::time_duration startTime (hour, minute, second);

		// End time
		cout << "Enter the end time (HH:MM):" << endl;
		cin >> hour>> colon>> minute;
		boost::posix_time::time_duration endTime (hour, minute, second);

		// Adding Course
		std::unique_ptr<Course> blockCourse
		(new BlockCourse(courseKey,title,
	    		major, creditPoint, startDate, endDate, startTime, endTime));
		db.addCourse(std::move(blockCourse));
		cout << ">>StudentDB: The new BlockCorse has been added" << endl;
	}

	//WeeklyCourse
	else if (courseType ==1)
	{
		cout<<"Enter the course day of week: "<<endl;
		cout<<"0. Sunday"<<endl;
		cout<<"1. Monday"<<endl;
		cout<<"2. Tuesday"<<endl;
		cout<<"3. Wednesday"<<endl;
		cout<<"4. Thursday"<<endl;
		cout<<"5. Friday"<<endl;
		cout<<"6. Saturday"<<endl;
		int dayInWeek;
		cin >> dayInWeek;
		boost::date_time::weekdays dayOfWeek =
				 static_cast<boost::date_time::weekdays>(dayInWeek);
		// Start time
		int hour, minute, second = 0;
		char colon;
		cout << "Enter the start time (HH:MM)" << endl;
		cin >> hour>> colon>> minute;
		boost::posix_time::time_duration startTime (hour, minute, second);

		// End time
		cout << "Enter the end time (HH:MM)" << endl;
		cin >> hour>> colon>> minute;
		boost::posix_time::time_duration endTime (hour, minute, second);

		// Adding Course
		std::unique_ptr<Course> weeklyCourse
		(new WeeklyCourse(courseKey,title,
	    		major, creditPoint, dayOfWeek, startTime, endTime));
		db.addCourse(std::move(weeklyCourse));
		cout << ">>StudentDB: The new WeeklyCourse has been added" << endl;
	}
}

void SimpleUI::listCourses()
{
	cout <<endl<<"---List Course---" << endl;
	const auto& courseList = db.getCourses();
	if (courseList.empty())
	{
		cout << ">>StudentDB: The course list is empty" << endl;
		return;
	}

	for(const auto& course : courseList)
	{
		const Course* pCourse = course.second.get();
		listCourseInDetail(pCourse);
		cout << "------------" << endl;
	}
	cout << ">>StudentDB: End Course List" << endl;
}

void SimpleUI::addStudent()
{
	cout << endl <<"-----------Add New Student---------" << endl;
	cout << "Enter firstName: ";
	string firstName;
	getline(cin>>ws, firstName);

	cout << "Enter lastName: ";
	string lastName;
	getline(cin>>ws, lastName);

	cout << "Enter date of Birth (DD.MM.YYYY): ";
	int day, month, year;
	char slash;
	cin >> day >> slash >> month >> slash >> year;
	boost::gregorian::date dateOfBirth (year, month, day);

	cout << "Enter street address: ";
	string street;
	getline(cin>>ws, street);

	cout << "Enter postal code: ";
	unsigned short postalCode;
	cin >> postalCode;

	cout << "Enter city name: ";
	string cityName;
	getline(cin>>ws, cityName);

	cout << "Enter additional info. If no enter 0" << endl;
	string additionalInfo;
	getline(cin>>ws, additionalInfo);

	if (additionalInfo == "0")
	{
		additionalInfo = "";
	}

	Address address(street,postalCode,cityName,additionalInfo);
	Student student (firstName, lastName, dateOfBirth, address);
	this->db.addStudent(student);

	cout << ">>StudentDB: A new student has been added" << endl;
	cout << ">>StudentDB: Matrikel number is: "
		 << student.getMatrikelNumber() << endl;
}

void SimpleUI::addEnrollment()
{
	cout << endl <<"-----------Add Enrollment---------" << endl;
	unsigned int matrikelNumber;
	while(true)
	{
		cout << "Enter matrikel numnber: " ;
		cin >> matrikelNumber;
		if (matrikelNumber == 0) return;

		if(db.validStudent(matrikelNumber))
		{
			break;
		}
		cout<<">>StudentDB: Not found student!!!"<<endl;
	}

	unsigned int courseKey;
	while(true)
	{
		cout << "Enter Course key: ";
		cin >> courseKey;

		if(db.validCourseKey(courseKey))
		{
			break;
		}
		cout<<">>StudentDB: Not found course!!!"<<endl;
	}

	cout << "Enter semester: ";
	string semester;
	getline(cin>>ws, semester);

	if(db.addEnrollment(matrikelNumber, courseKey, semester))
	{
		cout << ">>StudentDB: Add Enrollment successful" << endl;
	}
	else
	{
		cout <<">>StudentDB: Student has already enrolled this course" << endl;
	}
}

void SimpleUI::printStudent()
{
	cout << endl <<"-----------Print Student---------" << endl;
	unsigned int matrikelNumber;
	while(true)
	{
		cout << "Enter matrikel numnber: " ;
		cin >> matrikelNumber;
		if (matrikelNumber == 0) return;

		if(db.validStudent(matrikelNumber))
		{
			break;
		}
		cout<<"Not found student!!!"<<endl;
	}
	const Student& student = db.getStudentbyId(matrikelNumber);
	cout << ">>StudentDB:   Student information" << endl
		 << "First name:    " << student.getFirstName() << endl
		 << "Last name:     " << student.getLastName() << endl
		 << "Date of birth: " << student.getDateOfBirth() << endl
		 << "Street:        " << student.getAddress().getStreet() << endl
		 << "PostalCode:    " <<student.getAddress().getPostalCode() << endl
		 << "City Name:     " << student.getAddress().getCityName() << endl;
	if(student.getAddress().getAdditionalInfor() != "")
	{
		cout <<"Addl info:     "
			 << student.getAddress().getAdditionalInfor() << endl;
	}

	const auto& studentEnrollments = student.getEnrollments();
	if(studentEnrollments.empty())
	{
		cout << ">>StudentDB: This student does not have any enrollment"
			 << endl;
	}
	else
	{
		cout<< endl <<">>StudentDB:   Student Enrollment list:";
		for(const auto& enrollment: studentEnrollments)
		{
			const Course* course = enrollment.getCourse();
			listCourseInDetail(course);
			cout << "The grade is:  " << enrollment.getGrade() << endl
				 << "On semester:   " << enrollment.getSemester() << endl;
		}
	}
}

void SimpleUI::searchStudent()
{
	cout << endl <<"-----------Search Student---------" << endl;
	cout << "Enter the name of the searching student " << endl;
	string name;
	getline(cin>>ws, name);

	const std::vector<Student>& searchStudents = db.getStudentsbyName(name);
	cout << "List of full name students" << endl;
	for (const auto& searchStudent : searchStudents)
	{
		cout << "Student full name:  "
			 << searchStudent.getFirstName() << " "
			 << searchStudent.getLastName() << endl
			 << "Matrikel number is: "
			 << searchStudent.getMatrikelNumber() << endl
			 << "-------------------" << endl;
	}
}

void SimpleUI::updateStudent()
{
	cout << endl <<"-----------Update Student---------" << endl;

	// Ask for existing matrikel number
	unsigned int matrikelNumber;
	while(true)
	{
		cout << "Enter matrikel numnber: " ;
		cin >> matrikelNumber;
		if (matrikelNumber == 0) return;

		if(db.validStudent(matrikelNumber))
		{
			break;
		}
		cout<<">>StudentDB: Not found student!!!"<<endl;
	}

	// Print Out all informations of students
	Student& student = db.getStudentbyId(matrikelNumber);
		cout << ">>StudentDB: Student information" << endl
			 << "First name:    " << student.getFirstName() << endl
			 << "Last name:     " << student.getLastName() << endl
			 << "Date of birth: " << student.getDateOfBirth() << endl
			 << "Street:        " << student.getAddress().getStreet() << endl
			 << "PostalCode:    " << student.getAddress().getPostalCode()<<endl
			 << "City Name:     " << student.getAddress().getCityName() << endl;
		if(student.getAddress().getAdditionalInfor() != "")
		{
			cout << "Addl info:     "
				 << student.getAddress().getAdditionalInfor() << endl;
		}

		const auto& studentEnrollments = student.getEnrollments();
		if(studentEnrollments.empty())
		{
			cout << ">>StudentDB: This student does not have any enrollment"
				 << endl;
		}
		else
		{
			cout<< endl <<">>StudentDB: Student Enrollment list:";
			for(const auto& enrollment: studentEnrollments)
			{
				const Course* course = enrollment.getCourse();
				listCourseInDetail(course);
				cout << "The grade is:  " << enrollment.getGrade() << endl
					 << "On semester:   " <<enrollment.getSemester()<<endl;
			}
		}

	// Menu for which property to update
	while(true)
	{
		cout << endl <<"Update data list choices:" << endl
			 << "1. First name" << endl
			 << "2. Last name" << endl
			 << "3. Date of Birth" << endl
			 << "4. Address" << endl
			 << "5. Grade" << endl
			 << "6. Semester" << endl
			 << "7. Enrollment" << endl
			 << "0. Quit" << endl
			 << "Choose a number: ";
		int choice;
		cin >> choice;
		switch(choice)
		{
			case 1:
			{
				// Update first name
				cout << "Enter new first name: ";
				std::string newFirstName;
				getline(cin>>ws, newFirstName);
				student.setFirstName(newFirstName);
				cout << ">>StudentDB updated: New first name is "
					 << student.getFirstName() << endl;
				break;
			}
			case 2:
			{
				// Update last name
				cout << "Enter new last name: ";
				std::string newLastName;
				getline(cin>>ws, newLastName);
				student.setLastName(newLastName);
				cout << ">>StudentDB updated: New last name is "
					 << student.getLastName() << endl;
				break;
			}
			case 3:
			{
				// Update date of birth
				cout << "Enter new Date of Birth (DD.MM.YYYY): ";
				int day, month, year;
				char slash;
				cin >> day >> slash >> month >> slash >> year;
				boost::gregorian::date newDateOfBirth (year, month, day);
				student.setDateOfBirth(newDateOfBirth);
				cout << ">>StudentDB updated: New date of Birth is "
					 << student.getDateOfBirth() << endl;
				break;

			}
			case 4:
			{
				// Update address fields
				cout << "Enter new street address: ";
				string newStreet;
				getline(cin>>ws, newStreet);

				cout << "Enter new postal code: ";
				unsigned short newPostalCode;
				cin >> newPostalCode;

				cout << "Enter new city name: ";
				string newCityName;
				getline(cin>>ws, newCityName);

				cout << "Enter additional info. If no enter 0" << endl;
				string additionalInfo;
				getline(cin>>ws, additionalInfo);

				if (additionalInfo == "0")
				{
					additionalInfo = "";
				}

				Address newAddress(newStreet,newPostalCode,
									newCityName,additionalInfo);
				student.setAddress(newAddress);
				cout << ">>StudentDB update: New student address" << endl
					 << "Street: "
					 << student.getAddress().getStreet() << endl

					 << "PostalCode: "
					 <<student.getAddress().getPostalCode() << endl

					 << "City Name: "
					 << student.getAddress().getCityName() << endl;

					if(student.getAddress().getAdditionalInfor() != "")
					{
						cout << "Addl info:     "
							 << student.getAddress().getAdditionalInfor()
							 << endl;
					}

				break;
			}
			case 5:
			{
				// Update grade for a course
				unsigned int courseKey;
				while(true)
				{
					cout<<"Enter course key of course to update grade: ";
					cin >> courseKey;

					if(student.findEnrollmentByKey(courseKey))
					{
						break;
					}
					cout<<"Not found course!!!"<<endl;
				}
				cout << "Enter new grade: ";
				float newGrade;
				cin >> newGrade;
				student.setGrade(newGrade, courseKey);
				cout << ">>StudentDB updated: new Grade ";
				for (const auto& enrollment: student.getEnrollments())
				{
					if(enrollment.getCourse()->getCoursekey() == courseKey)
					{
						cout << enrollment.getGrade() << endl;
					}
				}
				break;
			}
			case 6:
			{
				// Update semester for a course
				unsigned int courseKey;
				while(true)
				{
					cout <<"Enter course key of course to update semester: ";
					cin >> courseKey;

					if(student.findEnrollmentByKey(courseKey))
					{
						break;
					}
					cout<<"Not found course!!!"<<endl;
				}
				cout << "Enter new semester: ";
				std::string newSemester;
				getline(cin>>ws, newSemester);
				student.setSemester(newSemester, courseKey);
				cout << ">>StudentDB updated: new Semester";
				for (const auto& enrollment: student.getEnrollments())
				{
					if(enrollment.getCourse()->getCoursekey() == courseKey)
					{
						cout << enrollment.getSemester() << endl;
					}
				}
				break;
			}
			case 7:
			{
				 // Delete enrollment for a selected course
				if(student.getEnrollments().empty())
				{
					cout<<
					">>StudentDB: This student have not enrolled any course."
							<<endl;
			    }
			    else{
			    	for(const Enrollment& enrollment:student.getEnrollments())
			    	{
			    		const Course* enrollCourse = enrollment.getCourse();
			    		listCourseInDetail(enrollCourse);
			    		cout<<"On "<<enrollment.getSemester()
			    				<<" semester"<< endl;
			    		cout<<"Grade: "<<enrollment.getGrade()<<endl;
			    	}
			    	cout<<"Enter the course key of the removing course: "<<endl;
					unsigned int courseKey;
					cin>>courseKey;

					if (student.deleteEnrollment(courseKey))
					{
						cout<<">>StudentDB: Remove the enrollment successfully."
								<<endl;
					}
					else
					{
						cout<<">>StudentDB: "
								"Invalid course key. Please try again."
								<<endl;
					}
			    }
				break;
			}
			case 0:
			{
				cout << "Quitting ....." ;
				return;
			}
			default: cout << "Invalid choice, try again !!!" << endl;
		}
	}

}

void SimpleUI::writeData()
{
	cout << endl <<"-----------Write Data---------" << endl;
	cout << "Enter the file name: ";
	string testWrite;
	getline(cin>>ws, testWrite);

	ofstream out(testWrite);
	if(!out)
	{
		cerr << "Error: cannot open file !!!" << endl;
		return;
	}

	db.write(out);
	cout << ">>StudentDB: Write to an external file done" << endl;
}

void SimpleUI::readData()
{
	cout << endl <<"-----------Read Data---------" << endl;
	cout << "Enter the file name: ";
	string testRead;
	getline(cin>>ws, testRead);

	ifstream in(testRead);
	if(!in)
	{
		cerr << "Error: cannot open file !!!" << endl;
		return;
	}

	db.read(in);
	cout << ">>StudentDB: Read to an external file done" << endl;
}

void SimpleUI::getDataFromServer() const
{
	cout<<"--Get Student data from server--"<<endl;
	int numberInput;
	cout<<"Enter the number of generating student from server: ";
	cin >> numberInput;
	if(numberInput <=0){
		cout<<"Invalid input!!!"<<endl;
		return;
	}
	cout << "Connecting... Please wait."<<endl;
	db.getDataFromServer(numberInput);

	cout<<">>StudentDB: Finish get Student data from server"<<endl;
}

// Print details for one course (including type-specific info)
void SimpleUI::listCourseInDetail(const Course *course)
{
	cout << endl
		 << "courseKey:     " << course->getCoursekey() << endl
		 << "Title:         " << course->getTitle() << endl
		 << "major:         " << course->getMajor() << endl
		 << "creditPoint:   " << course->getCreditPoint() << endl;

	if (const BlockCourse* blockCourse =
			dynamic_cast<const BlockCourse*>(course))
	{
		cout << "Course type:   Block" << endl
			 <<	"Start date:    "<<blockCourse->getStartDate() << endl
			 << "End date:      "<<blockCourse->getEndDate() << endl

			 << "Start time:    "<<blockCourse->getStartTime().hours()
			 <<":"<<(blockCourse->getStartTime().minutes()<10? "0":"")
			 <<blockCourse->getStartTime().minutes()<< endl

			 << "End time:      "<<blockCourse->getEndTime().hours()
			 <<":"<<(blockCourse->getEndTime().minutes()<10? "0":"")
			 <<blockCourse->getEndTime().minutes() <<endl;
	}

	if(const WeeklyCourse* weeklyCourse =
			dynamic_cast<const WeeklyCourse*>(course))
	{
		cout <<"Course type:   Weekly" << endl

			 <<"Start time:    "<<weeklyCourse->getStartTime().hours()
			 <<":"<<(weeklyCourse->getStartTime().minutes()<10? "0":"")
			 <<weeklyCourse->getStartTime().minutes()<< endl

			 <<"End time:      "<<weeklyCourse->getEndTime().hours()
			 <<":"<<(weeklyCourse->getEndTime().minutes()<10? "0":"")
			 <<weeklyCourse->getEndTime().minutes()<<endl

			 <<"Study on:      "
			 <<dayOfWeekToString(weeklyCourse->getDayOfWeek())
			 <<endl;
	}
}

void SimpleUI::run()
{
	while(true)
	{
		std::cout<< endl <<"-----Student Data Base-----"<<std::endl;
		std::cout<<"1.Add new Course"<<std::endl;
		std::cout<<"2.List course"<<std::endl;
		std::cout<<"3.Add new student"<<std::endl;
		std::cout<<"4.Add enrollment"<<std::endl;
		std::cout<<"5.Print student"<<std::endl;
		std::cout<<"6.Search student"<<std::endl;
		std::cout<<"7.Update student"<<std::endl;
		std::cout<<"8.Write to an external file"<<std::endl;
		std::cout<<"9.Read from an external file"<<std::endl;
		std::cout<<"10.Get data from server"<<std::endl;
		std::cout<<"0.Quit"<<std::endl;
		std::cout<<"Enter your choice by number: ";

		int command;
		std::cin>>command;

		switch(command)
		{
		case 1: addNewCourse(); break;
		case 2: listCourses(); break;
		case 3: addStudent(); break;
		case 4: addEnrollment(); break;
		case 5: printStudent(); break;
		case 6: searchStudent(); break;
		case 7: updateStudent(); break;
		case 8: writeData(); break;
		case 9: readData(); break;
		case 10: getDataFromServer(); break;
		case 0: cout << "Bye Bye....."; return;
		default: std::cout<<"Invalid choice!!!"<<std::endl; break;
		}
	}
}

