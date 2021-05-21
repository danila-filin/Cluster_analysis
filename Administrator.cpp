#include "Administrator.h"
#pragma warning (disable:4996)
#pragma warning (disable:4244)
#pragma warning (disable:4101)

Administrator::Administrator() {}

Administrator::Administrator(const Administrator& admin) { controller = admin.controller; }

const Administrator& Administrator::operator=(const Administrator& admin) { controller = admin.controller; return *this; }

void Administrator::open_log()
{
	ofstream log_file("LOG FILE.txt");
	log_file << "Process started\n\n";
	log_file.close();
}

void Administrator::read_command(char* command)
{
	ofstream log_file("LOG FILE.txt", ios::app);
	bool check_command;
    char* c=strtok(command, " ");
    string s, com(c);
    vector <string> args;
	double time_start, time_end, t_1, t_2;
	ifstream help;

    check_command = false;
    //if (command == "EXIT" || command == "exit" strcmp(command, "EXIT")==0 || )
    //{
    //    log_file << "The EXIT command was called -- successfully.\n\n";
    //    check_command = true;
    //}
    //if (command == "HELP" || command == "help")
    //{
    //    log_file << "The HELP command was called -- successfully.\n\n";
    //    check_command = true;
    //    help.open("HELP.txt");
    //    while (getline(help, s)) cout << s << endl;
    //    cout << "\n";
    //    help.close();
    //}
    //if (command == "INFO" || command == "info")
    //{
    //    log_file << "The INFO command was called -- successfully.\n\n";
    //    check_command = true;
    //}
    while (c != NULL) {
        c = strtok(NULL, " ");
        if (c == NULL) 
        {
            break;
        }
        args.push_back(c);
    }
    if (com == "GENERATE_CLOUD" || com == "generate_cloud")
    {
        if (args.size() == 0 && controller.get_analysis_state() == false) 
        { 
            controller.add_cloud_in_field(Cloud(0, 0, 1, 1, 100)); 
            log_file << "Generate cloud: 0 0 1 1 100 -- successfuly.\n\n";
        }
        if ((args.size() < 5 || args.size() > 5)  && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 5 && controller.get_analysis_state() == false)
        {
            controller.add_cloud_in_field(Cloud(stod(args[0]), stod(args[1]), stod(args[2]), stod(args[3]), stod(args[4])));
            log_file << "Generate cloud: " << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << " " << args[4] << " -- successfuly.\n\n";
        }
        if (controller.get_analysis_state() == true)
        {
            log_file << "Attempt to generate a cloud in the analysis state.\n\n";
        }
        check_command = true;
    }
    if (com == "DELETE_CLOUD" || com == "delete_cloud")
    {
        if ((args.size() == 0 || args.size() > 1) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && controller.get_analysis_state() == false)
        {
            controller.delete_cloud_from_field(stod(args[0]));
            log_file << "Delete " << args[0] << "-th cloud -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true)
        {
            log_file << "Attempt to delete a cloud in the analysis state.\n\n";
        }
        check_command = true;
    }
    if (com == "PRINT_FIELD" || com == "print_field")
    {
        controller.print_field();
        log_file << "Printing field to a file -- successfully.\n\n";
        check_command = true;
    }
    //Гистограммы
    if (com == "FIELD_HISTOGRAM" || com == "field_histogram")
    {
        if ((args.size() == 0 || args.size() > 1)) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            controller.creat_field_histogram(stod(args[0]));
            log_file << "Creating a histogram of the field with " << args[0] << " columns -- successfully.\n\n";
        }
        check_command = true;
    }
    if (com == "CLOUD_HISTOGRAM" || com == "cloud_histogram")
    {
        if ((args.size() < 2 || args.size() > 2)) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2)
        {
            controller.creat_cloud_histogram(stod(args[0]), stod(args[1]));
            log_file << "Creating a histogram of the " << args[0] << "-th cloud with " << args[1] << " columns -- successfully.\n\n";
        }
        check_command = true;
    }
    //Буфер
    if (com == "BUFFER_ADD_CLOUD" || com == "buffer_add_cloud")
    {
        if ((args.size() == 0 || args.size() > 1) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && controller.get_analysis_state() == false)
        {
            controller.add_cloud_from_field_in_buffer(stod(args[0]));
            log_file << "Add " << args[0] << "-th cloud from field in buffer -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to add cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_ADD_ALL_CLOUDS" || com == "buffer_add_all_clouds")
    {
        if (controller.get_analysis_state() == false)
        {
            controller.add_all_clouds_from_field_in_buffer();
            log_file << "Add all clouds from field in buffer -- successfully.\n\n";
        }
        else log_file << "Attempt to add clouds from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_UPLOAD_CLOUD" || com == "buffer_upload_cloud")
    {
        if ((args.size() == 0 || args.size() > 1) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && controller.get_analysis_state() == false)
        {
            controller.upload_cloud_from_buffer_in_field(stod(args[0]));
            log_file << "Upload " << args[0] << "-th cloud from the buffer in field -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to upload cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_UPLOAD_ALL_CLOUDS" || com == "buffer_upload_all_clouds")
    {
        if (controller.get_analysis_state() == false)
        {
            controller.upload_all_clouds_from_buffer_in_field();
            log_file << "Upload all clouds from the buffer in field -- successfully.\n\n";
        }
        else log_file << "Attempt to upload clouds from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_SHIFT_CLOUD" || com == "buffer_shift_cloud")
    {
        if ((args.size() < 3 || args.size() > 3) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 3 && controller.get_analysis_state() == false)
        {
            controller.shift_cloud_in_buffer(stod(args[0]), Vector(stod(args[1]), stod(args[2])));
            log_file << "Shift " << args[0] << "-th cloud in buffer by vector (" << args[1] << ", " << args[2] << ") -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to shift cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_SHIFT_ALL_CLOUDS" || com == "buffer_shift_all_clouds")
    {
        if ((args.size() < 2 || args.size() > 2) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2 && controller.get_analysis_state() == false)
        {
            controller.shift_all_clouds_in_buffer(Vector(stod(args[0]), stod(args[1])));
            log_file << "Shift all clouds in buffer by vector (" << args[0] << ", " << args[1] << ") -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to shift clouds from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_TURN_CLOUD" || com == "buffer_turn_cloud")
    {
        if ((args.size() < 2 || args.size() > 2) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2 && controller.get_analysis_state() == false)
        {
            controller.turn_cloud_in_bufffer(stod(args[0]), stod(args[1]));
            log_file << "Turn " << args[0] << "-th cloud in buffer at an angle " << args[1] << " -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to turn cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_TURN_ALL_CLOUDS" || com == "buffer_turn_all_clouds")
    {
        if ((args.size() < 1 || args.size() > 1) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && controller.get_analysis_state() == false)
        {
            controller.turn_all_clouds_in_bufffer(stod(args[0]));
            log_file << "Turn all clouds in buffer at an angle " << args[0] << " -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to turn clouds from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_COMPRESSION_CLOUD" || com == "buffer_compression_cloud")
    {
        if ((args.size() < 2 || args.size() > 2) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2 && controller.get_analysis_state() == false)
        {
            controller.compression_cloud_in_buffer(stod(args[0]), stod(args[1]));
            log_file << "Compression " << args[0] << "-th cloud in buffer -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to compression cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "BUFFER_COMPRESSION_ALL_CLOUDS" || com == "buffer_compression_all_clouds")
    {
        if ((args.size() < 1 || args.size() > 1) && controller.get_analysis_state() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && controller.get_analysis_state() == false)
        {
            controller.compression_all_clouds_in_buffer(stod(args[0]));
            log_file << "Compression all clouds in buffer -- successfully.\n\n";
        }
        if (controller.get_analysis_state() == true) log_file << "Attempt to compression clouds from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    //Алгоритмы
    if (com == "WAVE" || com == "wave")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the wave algorithm, delta=1";
            t_1 = clock();
            controller.wave(1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() > 1) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            log_file << "Starting the wave algorithm, delta=" << args[0];
            t_1 = clock();
            controller.wave(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "DBSCAN" || com == "dbscan")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the DBSCAN algorithm, delta=1, k=1";
            t_1 = clock();
            controller.dbscan(1, 1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() == 1 || args.size() > 2) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2)
        {
            log_file << "Starting the DBSCAN algorithm, delta=" << args[0] << ", k=" << args[1];
            t_1 = clock();
            controller.dbscan(stod(args[0]), stod(args[1]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "SPANNING_TREE" || com == "spanning_tree")
    {
        log_file << "Starting the spanning tree algorithm";
        t_1 = clock();
        controller.tree();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "K_MEANS" || com == "k_means")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the k means algorithm, k=1";
            t_1 = clock();
            controller.k_m(1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() > 1) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            log_file << "Starting the k means algorithm, k=" << args[0];
            t_1 = clock();
            controller.k_m(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "EM" || com == "em")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the em algorithm, k=1";
            t_1 = clock();
            controller.em(1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() > 1) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            log_file << "Starting the EM algorithm, k=" << args[0];
            t_1 = clock();
            controller.em(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "HIERARCHY" || com == "hierarchy")
    {
        log_file << "Starting the hierarchical algorithm";
        t_1 = clock();
        controller.hierarchy();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (check_command == false) log_file << "Entered command that could not be recognized.\n\n";
}