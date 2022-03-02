#include "tamagotchi.h"

void recept_result(void *ptr, size_t size, size_t nmemb, void *stream){
    char **response_ptr =  (char**)stream;
    *response_ptr = strndup(ptr, (size_t)(size *nmemb));
}

void get_weather(gpointer image){
  struct json_object  *json;
  struct json_object  *sys;
  struct json_object  *weather;
  char                url[299]="https://api.openweathermap.org/data/2.5/weather?q=paris&appid=bef7ea59a3ee61767331b57f9103a42d&lang=fr";
  char                res[300];
  CURL                *curl;
  CURLcode            resc;
  char                *result = calloc(1,sizeof(char));
  char                *file;

  strcpy(res,url);

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, res);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recept_result);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    resc = curl_easy_perform(curl);
    if (resc != CURLE_OK)
      curl_easy_cleanup(curl);
  }
  json = json_tokener_parse(result);
  json_object_object_get_ex(json, "weather", &sys);
  json_object_object_get_ex(json_object_array_get_idx(sys, 0), "main", &weather);

  const gchar *string_weather = json_object_get_string(weather);
  if (!strcmp(string_weather, "Clear")){
    printf("ok");
    file = "imgs/weather/sun.png";
  }else{
    if (!strcmp(string_weather, "Rain")){
      file = "imgs/weather/rain.png";
    }else{
      if (!strcmp(string_weather, "Snow")){
        file = "imgs/weather/snow.png";
      }else{
        file = "imgs/weather/cloud.png";
      }
    }
  }

  gtk_image_set_from_file(GTK_IMAGE(image), file);

  free(result);
}
