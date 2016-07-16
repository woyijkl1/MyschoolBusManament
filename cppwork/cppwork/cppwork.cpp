// cppwork.cpp : Defines the entry point for the console application.
//
//统一时间格式为：年份_月份_天_小时_分钟



#include "stdafx.h"
#include <string>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <time.h>  
#include <stdio.h>
#include <random>
#include <ctime>
using namespace std;


//时间类
class  get_time{
public:
	static void dsptime(const struct tm * ptm)
	{
		char *pxq[] = { "日", "一", "二", "三", "四", "五", "六" };
		cout << ptm->tm_year + 1900 << "年" << ptm->tm_mon + 1 << "月" << ptm->tm_mday << "日 ";
		cout << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << " ";
		cout << " 星期" << pxq[ptm->tm_wday] << endl;
	}
	static int now_time(struct tm * ptm){
		time_t nowtime;
		nowtime = time(NULL); //获取当前时间  
		localtime_s(ptm, &nowtime);
		return 1;
	}
	//获取通用格式的时间字符串
	static string formeddata(struct tm ptm){
		string temp;
		string temp2;
		char buffer[60];
		sprintf_s(buffer, "%d", ptm.tm_year + 1900);
		temp.assign(buffer);
		temp += "_";
		sprintf_s(buffer, "%d", ptm.tm_mon + 1);
		temp2.assign(buffer);
		temp += temp2;
		temp += "_";
		sprintf_s(buffer, "%d", ptm.tm_mday);
		temp2.assign(buffer);
		temp += temp2;
		temp += "_";
		sprintf_s(buffer, "%d", ptm.tm_hour);
		temp2.assign(buffer);
		temp += temp2;
		temp += "_";
		sprintf_s(buffer, "%d", ptm.tm_min);
		temp2.assign(buffer);
		temp += temp2;
		return temp;
	}
};

//各种卡在类的定义后直接声明了运行时的vector容器

//卡基类
class baseCard {

public:
	baseCard(string name, int cardnumber, int account, string type, string unit) :name(name), cardnumber(cardnumber), account(account), type(type), unit(unit), total_times(0), month_times(0), effective_time("2016_7_15"){
	};

public:
	string name;   //持卡人姓名
	string unit;   //所属单位
	string effective_time; //有效期
	int cardnumber;  //卡的编号
	int account;    //余额
	string type;   //卡的类别  有三类
	int total_times;
	int month_times;

public:
	static int total_stu_card_number;
	static int total_tea_card_number;
	static int total_res_card_number;

	//充值
	int recharge(int amount){
		account += amount;
		return 1;
	}


	//收费
public:
	virtual int charge(){
		int charges = 2;  // 每次乘车所收的费用
		account_remind();
		if (account < 2){
			cout << "amount of money is not enough,please recharge" << endl;
			return 0;
		}
		else{
			account -= charges;
			total_times++;
			month_times++; 
			cout << "name:" <<name<< '\t' << "account:" << account << endl;
			return 1;
		}

	}

	//金额题型
	int account_remind(){
		if (account < 5){
			cout << "your account is less than 5 yuan , you can get on after recharge" << endl;
		}
		return 0;
	}

	//每月的第一天将每月乘车次数清零
	int set_month_time(){
		struct tm nowtime;
		get_time::now_time(&nowtime);
		if (nowtime.tm_mday == 1){
			month_times = 0;
		}
		return 1;
	}

	//累计乘车次数
	int get_month_times(){
		cout << "this card have get on: " << month_times << " this month" << endl;
		return 1;
	}

	//统计总的卡数
	static int get_total_card_amount(){
		cout << "there totally are " << total_stu_card_number + total_tea_card_number + total_res_card_number << "  cards" << endl;
		cout << "total_stu_card_number: " << total_stu_card_number << endl;
		cout << "total_tea_card_number: " << total_tea_card_number << endl;
		cout << "total_res_card_number: " << total_res_card_number << endl;
		return 1;
	}


};
int baseCard::total_stu_card_number = 0;
int baseCard::total_tea_card_number = 0;
int baseCard::total_res_card_number = 0;


class student_card :public baseCard{
	using baseCard::baseCard;
public:
	student_card(string name, int cardnumber, int account) :baseCard(name, cardnumber, account, "student", "student_academy"){
		total_stu_card_number++;
	}

	friend ostream & operator<< (ostream &os, const student_card &stucard){
		os << "cardholder: " << stucard.name << "\t" << "card type: " << stucard.type << "\t" << "card number: " << stucard.cardnumber <<
			"\t" << "unit: " << stucard.unit << "\t" << "account: " << stucard.account << "\t" << "effective_time: "
			<< stucard.effective_time << endl;
		return os;
	}

};
vector<student_card> student_card_vector;


class teacher_card :public baseCard{
	using baseCard::baseCard;
public:
	teacher_card(string name, int cardnumber) :baseCard(name, cardnumber, 0, "teacher", "teacher_management"){
		total_tea_card_number++;
	};

	//收费
	int charge(){
			total_times++;
			month_times++;
			cout << "name:" << name << '\t' << "teacher_card:" << endl;
			return 1;

	}


	friend ostream & operator<< (ostream &os, const teacher_card &stucard){
		os << "cardholder: " << stucard.name << "\t" << "card type: " << stucard.type << "\t" << "card number: " << stucard.cardnumber <<
			"\t" << "unit: " << stucard.unit << "\t" << "effective_time: "
			<< stucard.effective_time << endl;
		return os;
	}
};
vector<teacher_card> teacher_card_vector;

class restrect_card :public baseCard{
	using baseCard::baseCard;
public:
	restrect_card(string name, int cardnumber, int account) :baseCard(name, cardnumber, account, "restrect", "card management"),free_times(0){
		total_res_card_number++;
	};

	int free_times;

	friend ostream & operator<< (ostream &os, const restrect_card &stucard){
		os << "cardholder: " << stucard.name << "\t" << "card type: " << stucard.type << "\t" << "card number: " << stucard.cardnumber <<
			"\t" << "unit: " << stucard.unit << "\t" << "account: " << stucard.account << "\t" << "effective_time: "
			<< stucard.effective_time << '\t'<<"free_times_count:"<< stucard.free_times<< endl;
		return os;
	}

	
	int charge(){
		int charges = 2;  // 每次乘车所收的费用
		if (free_times >= 20){
			account_remind();
			if (account < 2){
				cout << "amount of money is not enough,please recharge" << endl;
				return 0;
			}
			else{
				account -= charges;
				cout << "name  "<<name << '\t' << "account:" << account << endl;
				return 1;
			}
		}
		else{
			free_times++;
			if (free_times == 20){
				cout << "this is the last time for free" << endl;
			}
			cout << "name  " << name << '\t' << "account  " << account << endl;
		}
	return 1;
	}
	int set_free_time(){
		struct tm nowtime;
		get_time::now_time(&nowtime);
		if (nowtime.tm_mday == 1){
			free_times = 0;
		}

		return 1;
	}
};
vector<restrect_card> restrect_card_vector;

class bus_actual_run_information{
public:
	float occupancy_rate;  //载客率
	string actual_arriving_time;  //实际发车时间
	string acrtual_leaving_time;  //实际到达时间
	string daytime;//哪天发的车

	bus_actual_run_information(const bus_actual_run_information& temp) :occupancy_rate(temp.occupancy_rate), actual_arriving_time(temp.actual_arriving_time),
		acrtual_leaving_time(temp.acrtual_leaving_time), daytime(temp.daytime){
	};

	bus_actual_run_information() = default;

	friend ostream & operator<< (ostream &os, const bus_actual_run_information &bari){
		os << bari.occupancy_rate << "\t" << bari.actual_arriving_time << "\t" << bari.acrtual_leaving_time << '\t' << bari.daytime << endl;
		return os;
	}

};
//初始化
vector<bus_actual_run_information> bus1_actual_run_information_table;
vector<bus_actual_run_information> bus2_actual_run_information_table;


//运行时刻表
class bus_running_information{
public:
	string plate_name;
	string run_time;
	string leaving_time;
	string arrive_time;
	string whole_running_time;

	bus_running_information(string plate_name, string run_time, string leaving_time, string arrive_time,
		string whole_running_time) :plate_name(plate_name), run_time(run_time), leaving_time(leaving_time),
		arrive_time(arrive_time), whole_running_time(whole_running_time){
	};

	friend ostream & operator<< (ostream &os, const bus_running_information &bri){
		os << bri.plate_name << "\t" << bri.run_time << "\t" << bri.leaving_time <<
			"\t" << bri.arrive_time << "\t" << bri.whole_running_time << endl;
		return os;
	}

};
//初始化容器
vector<bus_running_information> bus_running_information_vector;




//每辆车的实际运行时间的统计表
class every_bus_run_information_statistics{
public:
	vector<bus_actual_run_information> statistics;
	string plate_name;
};

class bus_management{
	vector<bus_running_information> running_table;  //运行时刻表
	vector<every_bus_run_information_statistics> every_bus_run_infomation_statistics_table;  //所有车的实际运行时间


	int get_daily_information_table(){
		//统计信息
	}

};

class bus {
public:
	string plate_number;  //车牌号
	string type;  //车型
	int capacity;  //可载人数
	int got_number;  //已载人数
	string driver_name;  //司机姓名
	string run_time;  //运行时间

	string leaving_time;    //string类型的时间
	string arriving_time;   //string类型的时间
	struct tm tm_ltime;     //tm类型的出发时间
	struct tm tm_atime;		//tm类型的到达时间
	                        //应该把tm类型的时间转换成字符串给string类型的时间以输出


	bus(string plate_number, string type, int capacity, string driver_name,string run_time):plate_number
		(plate_number), type(type), capacity(capacity),driver_name(driver_name), run_time(run_time){
		leaving_time = "";
		arriving_time = "";
	}

	friend ostream & operator<< (ostream &os, const bus &bu){
		os << bu.plate_number << "\t" << bu.type << "\t" << bu.capacity <<
			"\t" << bu.driver_name << "\t" << bu.run_time << endl;
		return os;
	}

	int add_got_number(){
		if (got_number == capacity){
			cout << "this bus is already fully filled,please wait for the next one " << endl;
			return 0;
		}
		got_number++;
		return 1;
	}

	int leave(){
		get_time(&tm_ltime);
		leaving_time = get_time::formeddata(tm_ltime);//通用格式的离开时间
		return 1;
	}

	int arrive(vector<bus_actual_run_information> & info){
		get_time(&tm_atime);
		arriving_time = get_time::formeddata(tm_atime);//获取通用格式的时间字符串
		bus_actual_run_information temp;
		temp.daytime = arriving_time;                   //给时间函数啊！！
		temp.acrtual_leaving_time = leaving_time;
		temp.actual_arriving_time = arriving_time;
		temp.occupancy_rate = (float)got_number/(float)capacity;
		info.emplace_back(temp);
		
		got_number = 0;   //车上的人全部下车
		return 1;
	}
	

	//获取时间
	int get_time(struct tm * ptm){
		time_t nowtime;
		nowtime = time(NULL); //获取当前时间  
		localtime_s(ptm, &nowtime);
		return 1;
	}
};
//初始化车
vector<bus> bus_vector;


//持卡人类
class card_holder{
public:
	string name;   //持卡人姓名
	string sex;    //性别,1代表男 0代表女
	string post;   //职务
	string unit;   //所属单位
	string idnumber; //工资号 或者 学号 
	int times;      //乘坐次数

	//刷卡上车函数
	int charge(baseCard & card,bus& bs){
		if (bs.add_got_number()){     //判断车上的人满了没有
			card.charge();
			times++;
			return 1;
		}
		return 0;
	}
	card_holder(string name, string sex, string post, string unit, string idnumber,int times) :name(name), sex(sex),
		post(post), unit(unit), idnumber(idnumber), times(times){
	};


	//申请新卡
	int application(vector<student_card> & st_vector = student_card_vector, vector<teacher_card> & tea_vector = teacher_card_vector){
		if (post == "student"){  //申请学生类新卡
			st_vector.emplace_back(name, st_vector.size() + 1+10000, 50);  //初始金额设置为50元,学生卡号从10000开头
		}
		else{
			tea_vector.emplace_back(name, tea_vector.size() + 1 + 20000);  //教师类卡的卡号从20000开头
		}
		return 1;
	}

	//注销卡
	int written_off(baseCard&card, vector<student_card> & st_vector = student_card_vector, vector<teacher_card> & tea_vector = teacher_card_vector){
		if (card.type == "student"){
			//vector<student_card>::iterator iter;
			auto temp = student_card_vector.begin();
			while (temp != student_card_vector.end() && (*temp).cardnumber != card.cardnumber){
					temp++;
			}
			if ((*temp).cardnumber == card.cardnumber){
				student_card_vector.erase(temp);
				return 1;
			}
			else{
				cout << "card not found" << endl;
				return 0;
			}
		}
		else{
			auto temp = teacher_card_vector.begin();
			while (temp != teacher_card_vector.end() && (*temp).cardnumber != card.cardnumber){
				temp++;
			}
			if ((*temp).cardnumber == card.cardnumber){
				teacher_card_vector.erase(temp);
				return 1;
			}
			else{
				cout << "card not found" << endl;
				return 0;
			}
		}
	}

	//控制台输出持卡人所拥有的卡
	int card_holded(){
		if (post == "student"){
			for (auto &iter : student_card_vector){
				if (iter.name == name){
					cout << iter << endl;
				}
			}
		}
		else if (post == "teacher"){
			for (auto &iter : teacher_card_vector){
				if (iter.name == name){
					cout << iter << endl;
				}
			}
		}
		else{
			cout << "error" << endl;
		}

		return 1;
	}


	int card_exist(int card_number){
		if (post == "student"){
			for (auto &iter : student_card_vector){
				if (iter.cardnumber == card_number){
					return 1;
				}
			}
			cout << "can not find" << endl;
			return 0;
		}
		else if (post == "teacher"){
			for (auto &iter : teacher_card_vector){
				if (iter.cardnumber == card_number){
					return 1;
				}
			}
			cout << "can not find" << endl;
			return 0;
		}
		else{
			cout << "can not find" << endl;
			return 0;
		}
	}


	baseCard& find_card(int card_number){
		if (post == "student"){
			for (auto &iter : student_card_vector){
				if (iter.cardnumber == card_number){
					return iter;
				}
			}

		}
		else if (post == "teacher"){
			for (auto &iter : teacher_card_vector){
				if (iter.cardnumber == card_number){
					return iter;
				}
			}
		}
		else{
			cout << "can not find" << endl;
		}
	}

	friend ostream & operator<< (ostream &os, const card_holder &bu){
		os << bu.name << "\t" << bu.sex << "\t" << bu.post <<
			"\t" << bu.unit << "\t" << bu.idnumber <<'\t'<<bu.times<< endl;
		return os;
	}

};
//初始化
vector<card_holder> card_holder_vector;



//车站
class station{
public:
	string station_name;
	int station_number;
	int interval;
	


	station(string station_name, int station_number, int interval) :station_name(station_name), station_number(station_number),
		interval(interval){

	}

	friend ostream& operator<<(ostream& os, const station & sta){
		cout << "station name  " << sta.station_name << "\t\tstation number  " << sta.station_number << "\t\tinternal time  " << sta.interval << endl;
		return os;
	}

	
};

vector<station> station_vector;

//控制台交互
class interaction{
public:
	static void line(){
		cout << "---------------------------------------------------" << endl;
	}
	static void blankline(){
		cout << '\n' << endl;
	}
	static void home(){
		line();
		cout << "home page" << endl;
		blankline();
		cout << "1  for managing system imformation   \t\t\t2  for starting bus service" << endl;
		blankline();
		line();
	}
	static void information(){
		line();
		cout << "manage system imformation( 0 to quit )" << endl;
		blankline();

		cout << "1 for getting restrect cardholder imformation \t\t2 for getting student cardholder imformation" << endl;
		cout << "3 for getting teacher cardholder imformation \t\t4 for getting running table imformation" << endl;
		cout << "5 for getting actual bus1 run time imformation\t\t6 for getting actual bus2 run time imformation" << endl;
		cout << "7 for getting bus imformation\t\t\t\t8 for getting person imformation" << endl;
		cout << "9 for getting station imformation" << endl;
		blankline();
		line();
	}
	static void service(){
		line();
		cout << "service( 0 to quit )" << endl;
		blankline();
		cout << "1 for simulate bus running\t\t2 for applying for new card" << endl;
		cout << "3 for writing off card\t\t\t4 adding person" << endl;
		blankline();
		line();
	}
	static void information_switch(){
		int flag;
		while (cin >> flag){
			if (flag == 0)
				return;
			switch (flag){
			case 1:
				imformation1();
				information();
				break;
			case 2:
				imformation2();
				information();
				break;
			case 3:
				imformation3();
				information();
				break;
			case 4:
				imformation4();
				information();
				break;
			case 5:
				imformation5();
				information();
				break;
			case 6:
				imformation6();
				information();
				break;
			case 7:
				imformation7();
				information();
				break;
			case 8:
				imformation8();
				information();
				break;
			case 9:
				imformation9();
				information();
				break;
			default:
				printf("error\n");
				information();
			}
		}
	}
	static void service_switch(){
		int flag;
		while (cin >> flag){
			if (flag == 0)
				return;
			switch (flag){
			case 1:
				service1();
				service();
				break;
			case 2:
				service2(); 
				service();
				break;
			case 3:
				service3();
				service();
				break;
			case 4:
				service4();
				service();
				break;
			default:
				printf("error\n");
				service();
			}
		}
	}

	static void imformation1(){
		line();
		for (auto &iter : restrect_card_vector){
			cout << iter;
		}
		line();
	}
	static void imformation2(){
		line();
		for (auto &iter : student_card_vector){
			cout << iter;
		}
		line();
	}
	static void imformation3(){
		line();
		for (auto &iter : teacher_card_vector){
			cout << iter;
		}
		line();
	}
	static void imformation4(){
		line();
		for (auto& iter : bus_running_information_vector){
			cout << iter;
		}
		line();
	}

	static void imformation5(){
		line();
		for (auto& iter : bus1_actual_run_information_table){
			cout << iter;
		}
		line();
	}
	static void imformation6(){
		line();
		for (auto& iter : bus2_actual_run_information_table){
			cout << iter;
		}
		line();
	}
	static void imformation7(){
		line();
		for (auto &iter : bus_vector){
			cout << iter;
		}
		line();
	}
	static void imformation8(){
		line();
		for (auto &iter : card_holder_vector){
			cout << iter;
		}
		line();
	}
	static void imformation9(){
		line();
		for (auto & iter : station_vector){
			cout << "station name  " << iter.station_name<<"\t\tstation number  " <<iter.station_name<< "\t\tinterval time  " << iter.interval << endl;
		}
		line();

	}

	static void station_on_off(int bus_number1, station station_get , map<string, int> &off_station,int station_left){
		int person_number1;
		uniform_int_distribution<int> u(station_left + 1, station_vector.size() + 1);
		default_random_engine e(time(0));

		map<string, int>::iterator iter;
		for (iter = off_station.begin(); iter != off_station.end();){
			if ((*iter).second == station_get.station_number){
				cout << (*iter).first << "   get off	" << endl;
				iter = off_station.erase(iter);
				bus_vector[bus_number1 - 1].got_number--;
			}
			else{
				iter++;
			}
		}
		cout << "please choose person willing to take on(from 1 to end 0 for end)" << endl;
		line();
		for (auto &iter : card_holder_vector){
			cout << iter;
		}
		cout << "choose restrict card" << endl;
		line();
		while (cin >> person_number1 && person_number1 != 0){
			if (person_number1 > card_holder_vector.size() + 1){
				cout << "input error" << endl;
			}
			else{
				if (bus_vector[bus_number1 - 1].add_got_number()){
					cout << "please inter card number to charge" << endl;
					if (person_number1 == card_holder_vector.size() + 1){
						line();
						for (auto &iter : restrect_card_vector){
							cout << iter;
						}
						line();
						cout << "please inter card number to charge (from 1 to end and 0 to return)" << endl;
						int restrect_number;
						while (cin >> restrect_number && restrect_number != 0){
							if (restrect_number > restrect_card_vector.size()){
								cout << "card not found" << endl;
							}
							else{
								restrect_card_vector[restrect_number - 1].charge();
								off_station.insert(make_pair(restrect_card_vector[restrect_number - 1].name, u(e)));

							}
						}

					}
					else{
						card_holder_vector[person_number1 - 1].card_holded();
						int card_number_choose;
						while (cin >> card_number_choose){
							if (card_holder_vector[person_number1 - 1].card_exist(card_number_choose)){
								card_holder_vector[person_number1 - 1].find_card(card_number_choose).charge();
								off_station.insert(make_pair(card_holder_vector[person_number1 - 1].name, u(e)));
								break;
							}
						}
					}
				}
			}
			cout << "please choose person willing to take on(from 1 to end 0 for end)" << endl;
			line();
			for (auto &iter : card_holder_vector){
				cout << iter;
			}
			cout << "choose restrict card" << endl;
			line();
		}

	}

	void static service1(){
		cout << "bus list ..." << endl;
		line();
		for (auto &iter : bus_vector){
			cout << iter;
		}
		line();
		cout << "please choose which one(from 1 to end)" << endl;
		int bus_number1;
		cin >> bus_number1;
		if (bus_number1 > bus_vector.size()){
			cout << "input error\n" << endl;
			return;
		}
		cout << "please choose person willing to take on(from 1 to end 0 for end)" << endl;
		line();
		for (auto &iter : card_holder_vector){
			cout << iter;
		}
		cout << "choose restrict card" << endl;
		line();
		
		map<string, int> off_station;
		uniform_int_distribution<int> u(1, station_vector.size());
		default_random_engine e(time(0));
		int person_number1;
		bus_vector[bus_number1 - 1].got_number = 0;
		while (cin >> person_number1 && person_number1 != 0){
			if (person_number1 > card_holder_vector.size()+ 1){
				cout << "input error" << endl;
			}
			else{
				if (bus_vector[bus_number1 - 1].add_got_number()){
		
					cout << "please inter card number to charge" << endl;
					if (person_number1 == card_holder_vector.size() +1){
						line();
						for (auto &iter : restrect_card_vector){
							cout << iter;
						}
						line();
						cout << "please inter card number to charge (from 1 to end and 0 to return)" << endl;
						int restrect_number;
						while (cin >> restrect_number && restrect_number != 0){
							if (restrect_number > restrect_card_vector.size()){
								cout << "card not found" << endl;
							}
							else{
								restrect_card_vector[restrect_number - 1].charge();
								off_station.insert(make_pair(restrect_card_vector[restrect_number - 1].name, u(e)));

							}
						}
						
					}
					else{
						card_holder_vector[person_number1 - 1].card_holded();
						int card_number_choose;
						while (cin >> card_number_choose){
							if (card_holder_vector[person_number1 - 1].card_exist(card_number_choose)){
								card_holder_vector[person_number1 - 1].find_card(card_number_choose).charge();
								off_station.insert(make_pair(card_holder_vector[person_number1 - 1].name, u(e)));
								break;
							}
						}
					}
				}
			}
			cout << "please choose person willing to take on(from 1 to end 0 for end)" << endl;
			line();
			for (auto &iter : card_holder_vector){
				cout << iter;
			}
			cout << "choose restrict card" << endl;
			line();


		}
		cout << "bus leave..." << endl;
		bus_vector[bus_number1 - 1].leave();
		int station_left = 1;
		for (auto station : station_vector){
			cout << "station  " << station.station_name << "  arrive and will stop for  " << station.interval <<
				"passengers can get off and on " << endl;
			
			station_on_off(bus_number1, station, off_station,station_left);
			station_left++;
		}
		cout << "this bus has arrived at the terminal" << endl;
		map<string, int>::iterator iter;
		for (iter = off_station.begin(); iter != off_station.end();){
			cout << (*iter).first << "   get off	" << endl;
			iter = off_station.erase(iter);
		}
		bus_vector[bus_number1 - 1].arrive(bus1_actual_run_information_table);

	}


	void static service2(){
		cout << "card holder lists..." << endl;
		line();
		for (auto &iter : card_holder_vector){
			cout << iter;
		}
		line();
		cout << "please choose which one (1 to end by order)" << endl;
		int service2_flag;
		cin >> service2_flag;
		line();
		if (service2_flag <= card_holder_vector.size()){
			card_holder_vector[service2_flag - 1].application();
			cout << "application for new card successfully\n" << endl;
		}
		else{
			cout << "input error\n" << endl;
		}
	}
	void static service3(){
		cout << "card holder lists..." << endl;
		line();
		for (auto &iter : card_holder_vector){
			cout << iter;
		}
		line();
		cout << "please choose which one (1 to end by order)" << endl;
		int service3_flag;
		cin >> service3_flag;
		if (service3_flag > card_holder_vector.size()){
			cout << "input error\n" << endl;
			return;
		}

		line();
		card_holder_vector[service3_flag - 1].card_holded();
		line();
		cout << "please inter card number you want to wrriten off" << endl;
		int number_off;
		cin >> number_off;
		//判断卡是否存在
		if (card_holder_vector[service3_flag - 1].card_exist(number_off)){
			card_holder_vector[service3_flag - 1].written_off(card_holder_vector[service3_flag - 1].find_card(number_off));
			cout << "\nwritten off successfully..." << endl;
		}


	}
	void static service4(){
		string hname;   //持卡人姓名
		string hsex;    //性别,1代表男 0代表女
		string hpost;   //职务
		string hunit;   //所属单位
		string hidnumber; //工资号 或者 学号

		cout << "please inter name sex(1 for man 0 for woman ) post(teacher or student ) unit(teacher_management or student_academy) number(pay number(2000+) or student number())" << endl;
		cin >> hname>> hsex>> hpost >> hunit >> hidnumber;

			card_holder_vector.emplace_back(hname, hsex, hpost, hunit, hidnumber, 0);
			cout << "...\nperson is added successfully" << endl;

	}

};







int _tmain(int argc, _TCHAR* argv[])
{

	


	//初始化restrect卡
	//打开文件 文件地址为：D:\cppwork\restrectcardData.txt
	
	cout << "restrect card initialize..." << endl;
		ifstream restrect_in;
		ofstream restrect_out;
		restrect_out.open("D:\\cppwork\\restrectcardData.txt", ofstream::app);
		restrect_in.open("D:\\cppwork\\restrectcardData.txt");
		if (!restrect_in){
			cout << "error" << endl;
			return -1;
		}


		string name;	
		int cardnumber;
		int account;



		while (restrect_in >> name&&restrect_in >> cardnumber&&restrect_in >> account){
			
			restrect_card_vector.emplace_back(name, cardnumber, account);
		}
		for (auto &iter : restrect_card_vector){
			cout << iter;
		}

		//初始化student卡
		//打开文件 文件地址为：D:\cppwork\studentcardData.txt
		cout << "---------------------------------------------------" << endl;
		cout << "student card initialize..." << endl;
		ifstream student_in;
		ofstream student_out;
		student_out.open("D:\\cppwork\\studentcardData.txt", ofstream::app);
		student_in.open("D:\\cppwork\\studentcardData.txt");
		if (!student_in){
			cout << "error" << endl;
			return -1;
		}





		while (student_in >> name&&  student_in >> cardnumber&&  student_in >> account){

			student_card_vector.emplace_back(name, cardnumber, account);
		}
		for (auto &iter : student_card_vector){
			cout << iter;
		}
		student_in.close();
		student_out.close();

		//初始化teacher卡
		//打开文件 文件地址为：D:\cppwork\teachercardData.txt
		cout << "---------------------------------------------------" << endl;
		cout << "teacher card initialize..." << endl;
		ifstream teacher_in;
		ofstream teacher_out;
		teacher_out.open("D:\\cppwork\\teachercardData.txt", ofstream::app);
		teacher_in.open("D:\\cppwork\\teachercardData.txt");
		if (!teacher_in){
			cout << "error" << endl;
			return -1;
		}



		while (teacher_in >> name&&  teacher_in >> cardnumber){

			teacher_card_vector.emplace_back(name, cardnumber);
		}
		for (auto &iter : teacher_card_vector){
			cout << iter;
		}




	//初始化运行时刻表
		cout << "---------------------------------------------------" << endl;
		cout << "run time table initialize..." << endl;
		ifstream table_in;
		ofstream table_out;
		table_out.open("D:\\cppwork\\runningtable.txt", ofstream::app);
		table_in.open("D:\\cppwork\\runningtable.txt");
		if (!table_in){
			cout << "error" << endl;
			return -1;
		}
		
		string plate_name;
		string run_time;
		string leaving_time;
		string arrive_time;
		string whole_running_time;

		while (table_in >>plate_name &&table_in >> run_time &&table_in >> leaving_time&&table_in>>arrive_time&&table_in>>whole_running_time){
			bus_running_information_vector.emplace_back(plate_name, run_time, leaving_time, arrive_time, whole_running_time);
			//cout << info.plate_name << info.run_time << info.leaving_time << info.arrive_time << info.whole_running_time << endl;
		}

		for (auto& iter : bus_running_information_vector){
			cout << iter;
		}

		//初始化车每次实际运行时间
		cout << "---------------------------------------------------" << endl;
		cout << "actual bus1 runtime initialize..." << endl;
		ifstream bus1_actual_in;
		ofstream bus1_actual_out;
		bus1_actual_out.open("D:\\cppwork\\bus1rundata.txt", ofstream::app);
		bus1_actual_in.open("D:\\cppwork\\bus1rundata.txt");
		if (!bus1_actual_in){
			cout << "error" << endl;
			return -1;
		}
		
		bus_actual_run_information bari;
		while (bus1_actual_in >> bari.occupancy_rate &&bus1_actual_in >> bari.acrtual_leaving_time &&bus1_actual_in >> bari.actual_arriving_time &&bus1_actual_in >> bari.daytime){
			bus1_actual_run_information_table.emplace_back(bari);
		}
		for (auto& iter : bus1_actual_run_information_table){
			cout << iter;
		}




		//初始化车每次实际运行时间
		cout << "---------------------------------------------------" << endl;
		cout << "actual bus2 runtime initialize..." << endl;
		ifstream bus2_actual_in;
		ofstream bus2_actual_out;
		bus2_actual_out.open("D:\\cppwork\\bus2rundata.txt", ofstream::app);
		bus2_actual_in.open("D:\\cppwork\\bus2rundata.txt");
		if (!bus2_actual_in){
			cout << "error" << endl;
			return -1;
		}


		while (bus2_actual_in >> bari.occupancy_rate &&bus2_actual_in >> bari.acrtual_leaving_time &&bus2_actual_in >> bari.actual_arriving_time &&bus2_actual_in >> bari.daytime){
			bus2_actual_run_information_table.emplace_back(bari);
		}
		for (auto& iter : bus2_actual_run_information_table){
			cout << iter;
		}

		//初始化车
		cout << "---------------------------------------------------" << endl;
		cout << "bus initialize..." << endl;
		ifstream bus_in;
		ofstream bus_out;
		bus_out.open("D:\\cppwork\\busData.txt", ofstream::app);
		bus_in.open("D:\\cppwork\\busData.txt");
		if (!bus_in){
			cout << "error" << endl;
			return -1;
		} 
		string plate_number;  //车牌号
		string type;  //车型
		int capacity;  //可载人数
		int got_number;  //已载人数 
		string driver_name;  //司机姓名
		string bu_run_time;  //运行时间

	
		while (bus_in >> plate_number&&  bus_in >> type&&  bus_in >> capacity&& bus_in >> driver_name && bus_in >> bu_run_time){

			bus_vector.emplace_back(plate_number, type, capacity, driver_name, bu_run_time);
		}
		for (auto &iter : bus_vector){
			cout << iter;
		}

		//初始化人
		cout << "---------------------------------------------------" << endl;
		cout << "person initialize..." << endl;
		ifstream person_in;
		ofstream person_out;
		person_out.open("D:\\cppwork\\personData.txt", ofstream::app);
		person_in.open("D:\\cppwork\\personData.txt");
		if (!person_in){
			cout << "error" << endl;
			return -1;
		}
		string chname;   //持卡人姓名
		string chsex;    //性别,1代表男 0代表女
		string chpost;   //职务
		string chunit;   //所属单位
		string chidnumber; //工资号 或者 学号
		int chtimes;


		
		while (person_in >> chname&&  person_in >> chsex&&  person_in >> chpost&& person_in >> chunit && person_in >> chidnumber&& person_in >> chtimes){

			card_holder_vector.emplace_back(chname, chsex, chpost, chunit, chidnumber,chtimes);
		}
		for (auto &iter : card_holder_vector){
			cout << iter;
		}

		//初始化车站
		cout << "---------------------------------------------------" << endl;
		cout << "station initialize..." << endl;
		ifstream station_in;
		ofstream station_out;
		station_out.open("D:\\cppwork\\stationData.txt", ofstream::app);
		station_in.open("D:\\cppwork\\stationData.txt");
		if (!station_in){
			cout << "error" << endl;
			return -1;
		}
		
		string station_name;
		int station_number;
		int interval;



		while (station_in >> station_name&&  station_in >> station_number&&  station_in >> interval){

			station_vector.emplace_back(station_name,station_number,interval);
		}
		for (auto &iter : station_vector){
			cout << iter;
		}

		////申请新卡
		//cout << "---------------------------------------------------" << endl;
		//cout << "apply for new teacher card..." << endl;
		//card_holder_vector[0].application();
		//card_holder_vector[1].application();
		//for (auto &iter : teacher_card_vector){
		//	cout << iter;
		//}
		//cout << "---------------------------------------------------" << endl;
		//cout << "writen off lately applied teacher card..." << endl;
		////注销卡
		//card_holder_vector[0].written_off(teacher_card_vector.back());
		//card_holder_vector[1].written_off(teacher_card_vector.back());
		//for (auto &iter : teacher_card_vector){
		//	cout << iter;
		//}

		////模拟发车过程
		//cout << "---------------------------------------------------" << endl;
		//cout << "bus1 running..." << endl;
		//bus_vector[0].got_number = 3;
		//bus_vector[0].leave();
		//bus_vector[0].arrive(bus1_actual_run_information_table);
		//for (auto& iter : bus1_actual_run_information_table){
		//	cout << iter;
		//}

		cout << "---------------------------------------------------" << endl;


		//程序简易界面

		interaction::home();
		int flag;
		while (cin >> flag){
			switch (flag){
			case 1:
				interaction::information();
				interaction::information_switch();
				interaction::home();
				break;
			case 2:
				interaction::service();
				interaction::service_switch();
				interaction::home();
				break;
			default:
				printf("error\n");
			}
		}




	return 0;
}
