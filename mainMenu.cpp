//
// int MenuChinh()
// {
//     cout << "==========MENU CHINH========" << endl;
//     cout << "0. Thoat" << endl;
//     cout << "1. Bai 1" << endl;
//     cout << "2. Bai 2" << endl;
//     cout << "3. Bai 3" << endl;
//     return 3;
// }
// void XuLyMainMenuChinh(int &lenh)
// {
//     if (lenh == 1)
//     {
//         cout << "Chua lam duoc!!!" << endl;
//     }
//     else if (lenh == 2)
//     {
//         Cau02();
//     }
//     else if (lenh == 3)
//     {
//         Cau03();
//     }
//     if (lenh == 0)
//     {
//         char x;
//         cout << "Nhap y de thoat: ";
//         cin >> x;
//         if (x != 'y')
//         {
//             lenh = -1;
//         }
//     }
//     system("pause");
// }
// int run()
// {
//     int lenh = -1;
//     while (lenh != 0)
//     {
//         system("cls");
//         lenh = LuaChonXuLy(MenuChinh());
//         XuLyMainMenuChinh(lenh);
//     }
//     return 0;
// }