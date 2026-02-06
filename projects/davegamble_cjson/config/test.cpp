#include <iostream>
#include <cstring>
#include <cjson/cJSON.h>
#include <cjson/cJSON_Utils.h>

int main() {
    cJSON *root = cJSON_CreateObject();
    if (!root) return 1;
    cJSON_AddStringToObject(root, "name", "cJSON Test");
    cJSON_AddNumberToObject(root, "version", 1);

    cJSON *arr = cJSON_AddArrayToObject(root, "values");
    for (int i = 0; i < 3; ++i) {
        cJSON_AddItemToArray(arr, cJSON_CreateNumber(i*i));
    }

    char *printed = cJSON_PrintUnformatted(root);
    if (!printed) { cJSON_Delete(root); return 1; }

    cJSON *parsed = cJSON_Parse(printed);
    if (!parsed) { free(printed); cJSON_Delete(root); return 1; }
    cJSON *parsed2 = cJSON_Parse(printed);
    if (!parsed2) { cJSON_Delete(parsed); free(printed); cJSON_Delete(root); return 1; }

    int equal = cJSON_Compare(parsed, parsed2, 1);
    std::cout << "JSON: " << printed << "\nEqual: " << equal << std::endl;

    cJSON_Delete(parsed2);
    cJSON_Delete(parsed);
    free(printed);
    cJSON_Delete(root);
    return 0;
}
