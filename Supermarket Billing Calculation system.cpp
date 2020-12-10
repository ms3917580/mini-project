#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
class product 
    {
        int pno;
        char name[50];
        float price, qty, tax, dis;
        public:
            void create_product() 
            {
                cout << "\nPlease Enter The Product No. of The Product ";
                cin >> pno;
                cout << "\n\nPlease Enter The Name of The Product ";
                cin>>name;
                cout << "\nPlease Enter The Price of The Product ";
                cin >> price;
                cout << "\nPlease Enter The Discount (%) ";
                cin >> dis;
            }

        void display_product() 
        {
            cout << "\nThe Product No. of The Product : " << pno;
            cout << "\nThe Name of The Product : ";
            puts(name);
            cout << "\nThe Price of The Product : " << price;
            cout << "\nDiscount : " << dis;
        }

        int retpno() 
        {
            return pno;
        }

        float retprice() 
        {
            return price;
        }

        char * retname() 
        {
            return name;
        }

        int retdis() 
        {
            return dis;
        }

    };
    fstream fp;
    product pr;
    void write_product() 
    {
    fp.open("C:\\Users\\mohit\\Desktop\\shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
    }
    void display_all() 
    {
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("C:\\Users\\mohit\\Desktop\\shop.dat",ios::in);
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        pr.display_product();
        cout << "\n\n====================================\n";
    }
    fp.close();
    }
    void modify_product() 
    {
    	int no,found=0;
    	cout<<"\n Enter the product no whose record has to be updated:";
        cin>>no;
        fp.open("C:\\Users\\mohit\\Desktop\\shop.dat",ios::in|ios::out);
        while(fp.read((char*)&pr,sizeof(product)) && found==0)
        {
        	if(pr.retpno()==no)
       {
       	pr.display_product();
        cout<<"\n Enter the new details:-";
        pr.create_product();
        int location=(no-1)*sizeof(pr);
        fp.seekp(location);
        fp.write((char*)&pr,sizeof(pr));
        cout<<"\n\n\t Record updated";
        found=1;
    }
  }
  fp.close();
  if(found==0)
  cout<<"\n\n Record not found";
}
    void display_pp()
    {
    	int no;
    	fp.open("C:\\Users\\mohit\\Desktop\\shop.dat",ios::in|ios::out);
    	cout<<"\n Enter the product no whose record has to be opened:";
        cin>>no;
        int location=(no-1)*sizeof(pr);
        fp.seekp(location);
        fp.read((char*)&pr,sizeof(pr));
        pr.display_product();
	}
	void delete_product() 
	{
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("C:\\Users\\mohit\\Desktop\\shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("C:\\Users\\mohit\\Desktop\\Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        if (pr.retpno()!= no) 
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("C:\\Users\\mohit\\Desktop\\shop.dat");
    rename("C:\\Users\\mohit\\Desktop\\Temp.dat", "C:\\Users\\mohit\\Desktop\\shop.dat");
    cout << "\n\n\tRecord Deleted .."; 
    }
    void menu() 
    {
    fp.open("C:\\Users\\mohit\\Desktop\\shop.dat",ios::in);
    if (!fp) 
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create"; 
        cout << "\n\n\n Program is closing ....";
        exit(0);
    }
    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char*)&pr,sizeof(product))) 
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
    }   
    void place_order() 
    {
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n***************************";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n***************************\n";
    do 
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>> INVOICE <<<<<<<<<<<<<<<<<<<<<<<<<\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
    for (int x = 0; x <= c; x++) 
    {
        fp.open("C:\\Users\\mohit\\Desktop\\shop.dat", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof()) 
        {
            if (pr.retpno() == order_arr[x]) 
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
                cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
                    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
}
    int main()
    {
    	int pass;
    	string at;
    	cout<<"Enter account type(a/b):=";
    	cin>>at;
    	if(at=="a")
    	{
    		cout<<"enter password:=";
    		cin>>pass;
    		{
    			if(pass==2)
    			{
    				cout<<"--------------------------";
    				cout<<"\n"<<"\n"<<"Welcome to admin account";
    				int ch;
    				cout<<"\n"<<"Enter-1 to create new product";
    				cout<<"\n"<<"Enter-2 to show all products";
    				cout<<"\n"<<"Enter-3 to modify a product";
    				cout<<"\n"<<"Enter-4 to see record of a particular product";
    				cout<<"\n"<<"Enter-5 to delete record of a particular product";
    				cout<<"\n enter choice:=";
    				cin>>ch;
    				switch(ch)
    				{
    					case 1:
    						write_product();
    						break;
    					case 2:
    						display_all();
    						break;
    					case 3:
    						modify_product();
							break;		
						case 4:
							display_pp();
							break;
						case 5:
							delete_product();
							break; 
							
					}
    				
				}
				else
				{
					cout<<"wrong password";
				}
			}
		}
		else if(at=="b")
		{
			cout<<"Provide details for calculating bill";
			place_order(); 
		}
		else
		{
			cout<<"invalid input";
		}
	}

    
    
