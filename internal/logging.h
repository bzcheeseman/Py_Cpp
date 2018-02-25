//
// Created by Aman LaChapelle on 12/10/16.
//
// Py_C
// Copyright (c) 2016 Aman LaChapelle
// Full license at Py_C/LICENSE.txt
//

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PY_C_LOGGING_H
#define PY_C_LOGGING_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct _logs_t {
  char **files;
  int num_files;
}logs_t;

logs_t *new_logs(){
  logs_t *out = malloc(sizeof(logs_t));
  out->num_files = 0;
  out->files = malloc(sizeof(char *));

  return out;
}

FILE *_new_logfile(const char *logfile, logs_t* logs){
  FILE* log = fopen(logfile, "w+");
  logs->num_files += 1; //increment the number of logfiles
  logs->files = realloc(logs->files, sizeof(char *)*logs->num_files); //increase the size of the array of logfiles
  logs->files[logs->num_files-1] = logfile; //set the last item in the array to the new logfile

  return log;
}

FILE *_open_logfile(const char *logfile, logs_t *logs){
  int n_logs = logs->num_files;
  if (n_logs > 0){
    bool found = false;
    for (int i = 0; i < n_logs; i++){
      if (strcmp(logfile, logs->files[i]) == 0){
        found = true;
        break;
      }
    }
    if (found){
      FILE *log = fopen(logfile, "a+");
      fseek(log, 0, SEEK_END);
      return log;
    }
    else{
      FILE *log = _new_logfile(logfile, logs);
      return log;
    }
  }
  else{
    FILE *log = _new_logfile(logfile, logs);
    return log;
  }

  return NULL;

}

void print_logfiles(logs_t *logs){
  int n_logs = logs->num_files;
  for (int i = 0; i < n_logs; i++){
    printf("File: %s, Index: %d\n", logs->files[i], i);
  }
}

void to_log(const char *logfile, const char *to_log, logs_t *logs){
  FILE *log = _open_logfile(logfile, logs);
  if (log){
    fprintf(log, "%s\n", to_log);
    fclose(log);
  }
}

void close_log(logs_t *logs){
  int n_logs = logs->num_files;
  free(logs);
}


#endif //PY_C_LOGGING_H
