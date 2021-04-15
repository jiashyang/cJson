/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//定义一个　cJSON结构 add 2021.04.14 by J
/* The cJSON structure: */
//typedef struct cJSON {
//	struct cJSON *next,*prev;	/* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
//	struct cJSON *child;		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
//	int type;					/* The type of the item, as above. */
//	char *valuestring;			/* The item's string, if type==cJSON_String */
//	int valueint;				/* The item's number, if type==cJSON_Number */
//	double valuedouble;			/* The item's number, if type==cJSON_Number */
//	char *string;				/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
//} cJSON;

//typedef struct cJSON_Hooks {
//      void *(*malloc_fn)(size_t sz);
//      void (*free_fn)(void *ptr);
//} cJSON_Hooks;

//extern void cJSON_InitHooks(cJSON_Hooks* hooks);
/* Supply a block of JSON, and this returns a cJSON object you can interrogate. Call cJSON_Delete when finished. */
//extern cJSON *cJSON_Parse(const char *value);
/* Render a cJSON entity to text for transfer/storage. Free the char* when finished. */
//extern char  *cJSON_Print(cJSON *item);
/* Render a cJSON entity to text for transfer/storage without any formatting. Free the char* when finished. */
//extern char  *cJSON_PrintUnformatted(cJSON *item);
/* Render a cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
//extern char *cJSON_PrintBuffered(cJSON *item,int prebuffer,int fmt);
/* Delete a cJSON entity and all subentities. */
//extern void   cJSON_Delete(cJSON *c);
/* Returns the number of items in an array (or object). */
//extern int	  cJSON_GetArraySize(cJSON *array);
/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
//extern cJSON *cJSON_GetArrayItem(cJSON *array,int item);
/* Get item "string" from object. Case insensitive. */
//extern cJSON *cJSON_GetObjectItem(cJSON *object,const char *string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds. */
//extern const char *cJSON_GetErrorPtr(void);
/* These calls create a cJSON item of the appropriate type. */
//extern cJSON *cJSON_CreateNull(void);
//extern cJSON *cJSON_CreateTrue(void);
//extern cJSON *cJSON_CreateFalse(void);
//extern cJSON *cJSON_CreateBool(int b);
//extern cJSON *cJSON_CreateNumber(double num);
//extern cJSON *cJSON_CreateString(const char *string);
//extern cJSON *cJSON_CreateArray(void);
//extern cJSON *cJSON_CreateObject(void);
/* These utilities create an Array of count items. */
//extern cJSON *cJSON_CreateIntArray(const int *numbers,int count);
//extern cJSON *cJSON_CreateFloatArray(const float *numbers,int count);
//extern cJSON *cJSON_CreateDoubleArray(const double *numbers,int count);
//extern cJSON *cJSON_CreateStringArray(const char **strings,int count);
/* Append item to the specified array/object. */
//extern void cJSON_AddItemToArray(cJSON *array, cJSON *item);
//extern void	cJSON_AddItemToObject(cJSON *object,const char *string,cJSON *item);
//extern void	cJSON_AddItemToObjectCS(cJSON *object,const char *string,cJSON *item);	/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the cJSON object */
/* Append reference to item to the specified array/object. Use this when you want to add an existing cJSON to a new cJSON, but don't want to corrupt your existing cJSON. */
//extern void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
//extern void	cJSON_AddItemReferenceToObject(cJSON *object,const char *string,cJSON *item);
/* Remove/Detatch items from Arrays/Objects. */
//extern cJSON *cJSON_DetachItemFromArray(cJSON *array,int which);
//extern void   cJSON_DeleteItemFromArray(cJSON *array,int which);
//extern cJSON *cJSON_DetachItemFromObject(cJSON *object,const char *string);
//extern void   cJSON_DeleteItemFromObject(cJSON *object,const char *string);
/* Update array items. */
//extern void cJSON_InsertItemInArray(cJSON *array,int which,cJSON *newitem);	/* Shifts pre-existing items to the right. */
//extern void cJSON_ReplaceItemInArray(cJSON *array,int which,cJSON *newitem);
//extern void cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
/* Duplicate a cJSON item */
//extern cJSON *cJSON_Duplicate(cJSON *item,int recurse);
/* Duplicate will create a new, identical cJSON item to the one you pass, in new memory that will
need to be released. With recurse!=0, it will duplicate any children connected to the item.
The item->next and ->prev pointers are always zero on return from Duplicate. */
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
//extern cJSON *cJSON_ParseWithOpts(const char *value,const char **return_parse_end,int require_null_terminated);
//extern void cJSON_Minify(char *json);
//以上外部声明函数，可以通过引用头文件定义

#include <dlfcn.h> //动态库加载头文件
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
	char *out;cJSON *json;
	
	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);
		free(out);
	}
}

/* Read a file, parse, render back, etc. */
void dofile(char *filename)
{
	FILE *f;long len;char *data;
	
	f=fopen(filename,"rb");fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
	data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
	doit(data);
	free(data);
}

/* Used by some code below as an example datatype. */
struct record {const char *precision;double lat,lon;const char *address,*city,*state,*zip,*country; };

/* Create a bunch of objects as demonstration. */
void create_objects()
{
	cJSON *root,*fmt,*img,*thm,*fld;char *out;int i;	/* declare a few. */
	/* Our "days of the week" array: */
	const char *strings[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	/* Our matrix: */
	int numbers[3][3]={{0,-1,0},{1,0,0},{0,0,1}};
	/* Our "gallery" item: */
	int ids[4]={116,943,234,38793};
	/* Our array of "records": */
	struct record fields[2]={
		{"zip",37.7668,-1.223959e+2,"","SAN FRANCISCO","CA","94107","US"},
		{"zip",37.371991,-1.22026e+2,"","SUNNYVALE","CA","94085","US"}};

	/* Here we construct some JSON standards, from the JSON site. */
	
	/* Our "Video" datatype: */
	root=cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1920);
	cJSON_AddNumberToObject(fmt,"height",		1080);
	cJSON_AddFalseToObject (fmt,"interlace");
	cJSON_AddNumberToObject(fmt,"frame rate",	24);
	
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);	/* Print to text, Delete the cJSON, print it, release the string. */

	/* Our "days of the week" array: */
	root=cJSON_CreateStringArray(strings,7);

	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);

	/* Our matrix: */
	root=cJSON_CreateArray();
	for (i=0;i<3;i++) cJSON_AddItemToArray(root,cJSON_CreateIntArray(numbers[i],3));

/*	cJSON_ReplaceItemInArray(root,1,cJSON_CreateString("Replacement")); */
	
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);


	/* Our "gallery" item: */
	root=cJSON_CreateObject();
	cJSON_AddItemToObject(root, "Image", img=cJSON_CreateObject());
	cJSON_AddNumberToObject(img,"Width",800);
	cJSON_AddNumberToObject(img,"Height",600);
	cJSON_AddStringToObject(img,"Title","View from 15th Floor");
	cJSON_AddItemToObject(img, "Thumbnail", thm=cJSON_CreateObject());
	cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
	cJSON_AddNumberToObject(thm,"Height",125);
	cJSON_AddStringToObject(thm,"Width","100");
	cJSON_AddItemToObject(img,"IDs", cJSON_CreateIntArray(ids,4));

	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);

	/* Our array of "records": */

	root=cJSON_CreateArray();
	for (i=0;i<2;i++)
	{
		cJSON_AddItemToArray(root,fld=cJSON_CreateObject());
		cJSON_AddStringToObject(fld, "precision", fields[i].precision);
		cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
		cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
		cJSON_AddStringToObject(fld, "Address", fields[i].address);
		cJSON_AddStringToObject(fld, "City", fields[i].city);
		cJSON_AddStringToObject(fld, "State", fields[i].state);
		cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
		cJSON_AddStringToObject(fld, "Country", fields[i].country);
	}
	
/*	cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root,1),"City",cJSON_CreateIntArray(ids,4)); */
	
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);

}

int main (int argc, const char * argv[]) {
/*
	//初始化接口 add 2021.04.14 by J
	typedef cJSON* (*pJSON_Parse)(const char *value);
	pJSON_Parse cJSON_Parse;

	//加载动态库
	void *hDLL_test=dlopen("./libtestso.so",RTLD_LAZY);
	if(hDLL_test=NULL){
		printf("testso.so load error\n");
		getchar();
		return -1;
	};
	char *pszErr = dlerror();
	if(pszErr != NULL){
		printf("%s\n",pszErr);
		return 0;
	}
	//链接动态库中得到函数接口
	cJSON_Parse = (pJSON_Parse)dlsym(hDLL_test,"cJSON_Parse");
*/
	/* a bunch of json: */
	char text1[]="{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";	
	char text2[]="[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
	char text3[]="[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
	char text4[]="{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
	char text5[]="[\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";

	/* Process each json textblock by parsing, then rebuilding: */
	doit(text1);
	doit(text2);	
	doit(text3);
	doit(text4);
	doit(text5);

	/* Parse standard testfiles: */
/*	dofile("../../tests/test1"); */
/*	dofile("../../tests/test2"); */
/*	dofile("../../tests/test3"); */
/*	dofile("../../tests/test4"); */
/*	dofile("../../tests/test5"); */

	/* Now some samplecode for building objects concisely: */
	create_objects();
	
	return 0;
}
