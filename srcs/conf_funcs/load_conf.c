#include "tamagotchi.h"

int			isWhiteSpace(char c) {
	return (c == ' ' || c == '\f' || c == '\t' || c == '\n'
			|| c == '\r' || c == '\v');
}

char			*trim(char *str) {
	int		start;
	int		end;
	int		len;
	char		*trimed_str;

	start = 0;
	while (isWhiteSpace(str[start]) && str[start] != '\0') {
		start++;
	}

	if (str[start] == '\0') {
		return (NULL);
	}

	end = strlen(str) - 1;

	while(isWhiteSpace(str[end]) && end > 0) {
		end--;
	}
	

	len = end - start + 1; // doing end - start gives the length minus one.


	if (end == 0 || len <= 0) {
		return (NULL);
	}

	trimed_str = (char*)malloc(sizeof(char) * (len + 1));
	trimed_str[len] = '\0';

	return (strncpy(trimed_str, &str[start], len));
}

int			validateBool(char *val) {
	if (!strcmp(val, "true") || !strcmp(val, "false")) {
		return (1);
	}
	return (0);
}

int			validateNumber(char *val) {
	if (*val == '+' || *val == '-') {
		val++;
	}
	while (*val) {
		if (*val < '0' || *val > '9') {
			return (0);
		}
		val++;
	}
	return (1);
}


int			assign(s_config *conf, char *key, char *value) {
	size_t		value_len;

	if (!strcmp(key, "display_healthbar")) {
		if (!validateBool(value)) {
			return (0);
		}
		conf->display_healthbar = !strcmp(value, "true") ? 1 : 0;
		return (1);
	}
	if (!strcmp(key, "display_hungerbar")) {
		if (!validateBool(value)) {
			return (0);
		}
		conf->display_hungerbar = !strcmp(value, "true") ? 1 : 0;
		return (1);
	}
	if (!strcmp(key, "display_funbar")) {
		if (!validateBool(value)) {
			return (0);
		}
		conf->display_funbar = !strcmp(value, "true") ? 1 : 0;
		return (1);
	}
	if (!strcmp(key, "display_hygienebar")) {
		if (!validateBool(value)) {
			return (0);
		}
		conf->display_hygienebar = !strcmp(value, "true") ? 1 : 0;
		return (1);
	}
	if (!strcmp(key, "hunger_frequency")) {
		if (!validateNumber(value)) {
			return (0);
		}
		conf->hunger_frequency = atoi(value);
		return (1);
	}if (!strcmp(key, "work_duration")) {
		if (!validateNumber(value)) {
			return (0);
		}
		conf->work_duration = atoi(value);
		return (1);
	}
	if (!strcmp(key, "grow_time")) {
		if (!validateNumber(value)) {
			return (0);
		}
		conf->grow_time = atoi(value);
		return (1);
	}
	if (!strcmp(key, "hide_and_seek_duration")) {
		if (!validateNumber(value)) {
			return (0);
		}
		conf->hide_and_seek_duration = atoi(value);
		return (1);
	}
	if (!strcmp(key, "dictation_duration")) {
		if (!validateNumber(value)) {
			return (0);
		}
		conf->dictation_duration = atoi(value);
		return (1);
	}
	if (!strcmp(key, "location")) {
		value_len = strlen(value);
		conf->location = (char*)malloc(sizeof(char) * (value_len + 1));
		strncpy(conf->location, value, value_len + 1);

		return (1);
	}

	return (-1);
}

s_config		*load_conf(char *conf_path) {
	s_config	*config;
	FILE		*file;
	char		buff[BUFF_SIZE];
	char		*field;
	char		*value;
	int		field_length;
	int		assign_ret;

	if (!(file = fopen(conf_path, "r"))) {
		printf("Couldn't open config file.");
		exit(EXIT_FAILURE);
	}

	config = (s_config*)malloc(sizeof(s_config) * 1);

	while (fgets(buff, BUFF_SIZE, file)) {
		buff[strlen(buff) - 1] = '\0'; // remove ending '\n'
		field_length = 0;
		while (buff[field_length] != '\0' && buff[field_length] != ':'
				&& buff[field_length] != ' ') {
			field_length++;
		}

		if (buff[field_length] == '\0' || field_length == 0) {
			printf("Error: invalid config line");
			return (NULL);
		}

		field = (char*)malloc(sizeof(char) * (field_length + 1));
		strncpy(field, buff, field_length);
		field[field_length] = '\0';

		if (!(value = strchr(buff, ':'))) {
			free(field);
			free_conf(config);
			printf("Error: invalid config line");
			return (NULL);
		}

		value = trim(value + 1);

		assign_ret = assign(config, field, value);
		if (assign_ret <= 0) {
			
			if (assign_ret == -1) {
				printf("Error: invalid field: %s\n", field);
			}
			if (assign_ret == 0) {
				printf("Error: invalid value '%s' for field '%s'\n", value, field);
			}

			free_conf(config);
			free(field);
			free(value);
			return (NULL);
		}

		free(field);
		free(value);
	}


	fclose(file);

	return (config);
}
