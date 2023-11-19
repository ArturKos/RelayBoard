#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "crc.h"
#include "main.h"

unsigned char message_to_board[MESSAGE_TO_BOARD_LENGTH] = {0x55,0x01,'S',0xff,0x28};
unsigned char power_strip_device[POWER_STRIP_DEVICE_CONTROL_NAME_LENGTH] = {0};

bool read_config_file(){

   FILE *config_file = fopen(POWER_STRIP_CONFIG_FILE_NAME, "r+");
   
   if (NULL == config_file){
		return false;
	}
	int read_count = fread( power_strip_device, sizeof(char), POWER_STRIP_DEVICE_CONTROL_NAME_LENGTH, config_file);
    if (0 == read_count){
		fclose(config_file);
		return false;
	}
	power_strip_device[read_count-1] = 0;
	fclose(config_file); 
	return true;
}

void board_setup(){
	char setup_device_command[SETUP_DEVICE_COMMAND_BUF_LEN] = {0};
	sprintf(setup_device_command,"stty -F %s 57600 cs8 -cstopb -parity -icanon min 100 time 1", power_strip_device);
	system(setup_device_command);
}

bool board_get_relays_status(){
	
	unsigned char reply_message_from_board[MESSAGE_TO_BOARD_LENGTH] = {0};

	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_ON;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_GET_STATUS;
    message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

    FILE *board = fopen((char *)power_strip_device, "r+");
	if (NULL == board){
		return false;
	}
    if (MESSAGE_TO_BOARD_LENGTH != fwrite( message_to_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)){
		fclose(board);
		return false;
	}
    if (MESSAGE_TO_BOARD_LENGTH != fread( reply_message_from_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)){
		fclose(board);
		return false;
	}

	for(int relay_idx = 0; relay_idx<8; relay_idx++){
		if(reply_message_from_board[RELAYS_MESSAGE_RELAY_INDEX] & (1<<relay_idx))
			printf("Relay %d is on\n", relay_idx+1);
		else
			printf("Relay %d is off\n", relay_idx+1);
	}
	fclose(board);
 	return true;
}
bool board_write_message_to_board(){

    FILE *board = fopen((char *)power_strip_device, "r+");
	if (NULL == board){
		return false;
	}
    if (MESSAGE_TO_BOARD_LENGTH != fwrite( message_to_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)){
		fclose(board);
		return false;
	}
    fclose(board);
	return true;

}

bool board_switch_all_on(){
	
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_ON;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_SET_STATUS;
    message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

    return board_write_message_to_board(message_to_board);
}

bool board_switch_all_off(){
	
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_OFF;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_SET_STATUS;
    message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

    return board_write_message_to_board(message_to_board);
}

bool board_switch_on(unsigned char relay_number){
	
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = relay_number;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_ON;
    message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

    return board_write_message_to_board(message_to_board);
}

bool board_switch_off(unsigned char relay_number){
	
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = relay_number;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_OFF;
    message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

    return board_write_message_to_board(message_to_board);
}

void print_usage_message(){
		printf("Usage:\n");
		printf("1. power_strip status\n");
		printf("2. power_strip allon\n");
		printf("3. power_strip alloff\n");
		printf("4. power_strip X on  (X - relay number from 1 to 8\n");
		printf("5. power_strip X off (X - relay number from 1 to 8\n");
}

int main(int argc, char *argv[]){
	
	if(!read_config_file()){
		printf("Error loading config file: %s\n", POWER_STRIP_CONFIG_FILE_NAME);
		return -1;
	}

	if(argc !=2 && argc!=3){
		print_usage_message();
	    return -1;
	}

	board_setup();

	if(argc == 2){
		if(0 == strcmp(argv[1], "allon")){
			if (board_switch_all_on() ){
				printf("Switched all relays on\n");
				return 0;
			}else
			{
				printf("Error switching all relays to on\n");
				return 1;			
			}
		}
		if(0 == strcmp(argv[1], "alloff")){
			if (board_switch_all_off() ){
				printf("Switched all relays off\n");
				return 0;
			}else
			{
				printf("Error switching all relays to off\n");
				return 1;			
			}
		}
		if(0 == strcmp(argv[1], "status")){
			if (board_get_relays_status() ){
				return 0;
			}else
			{
				printf("Error getting status of relays\n");
				return 1;			
			}
		}
	}

	if(argc == 3){
		char switch_idx = atoi(argv[1]);
		if( 0 == switch_idx || ((switch_idx - 1) < MIN_RELAY_IDX ) || ((switch_idx -1)> MAX_RELAY_IDX) ){
			print_usage_message();
    		return -1;		
		}
		if(0 == strcmp(argv[2], "on")){
			if (board_switch_on(switch_idx - 1) ){
				printf("Switched relay on\n");
				return 0;
			}else
			{
			print_usage_message();
    		return -1;				
			}
		}
		if(0 == strcmp(argv[2], "off")){
			if (board_switch_off(switch_idx - 1) ){
				printf("Switched relay off\n");
				return 0;
			}else
			{
			 print_usage_message();
    		 return -1;				
			}
		}
	}

	print_usage_message();
    return -1;
}