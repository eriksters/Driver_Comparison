#include "DataGen.h"
#include "string.h"

char data[] = "\n\
Whenever life gets you down, Mrs.Brown\n\
And things seem hard or tough\n\
And people are stupid, obnoxious or daft\n\
And you feel that you've had quite enough\n\
\n\
Just remember that you're standing on a planet that's evolving\n\
And revolving at nine hundred miles an hour\n\
That's orbiting at nineteen miles a second, so it's reckoned\n\
A sun that is the source of all our power\n\
\n\
The sun and you and me and all the stars that we can see\n\
Are moving at a million miles a day\n\
In an outer spiral arm, at forty thousand miles an hour\n\
Of the galaxy we call the 'milky way'\n\
\n\
Our galaxy itself contains a hundred billion stars\n\
It's a hundred thousand light years side to side\n\
It bulges in the middle, sixteen thousand light years thick\n\
But out by us, it's just three thousand light years wide\n\
\n\
We're thirty thousand light years from galactic central point\n\
We go 'round every two hundred million years\n\
And our galaxy is only one of millions of billions\n\
In this amazing and expanding universe\n\
\n\
The universe itself keeps on expanding and expanding\n\
In all of the directions it can whizz\n\
As fast as it can go, the speed of light, you know\n\
Twelve million miles a minute and that's the fastest speed there is\n\
\n\
So remember, when you're feeling very small and insecure\n\
How amazingly unlikely is your birth\n\
And pray that there's intelligent life somewhere up in space\n\
'Cause it's bugger all down here on Earth\n\
-----------\n\
ONE MORE TIME!\n\
Whenever life gets you down, Mrs.Brown\n\
And things seem hard or tough\n\
And people are stupid, obnoxious or daft\n\
And you feel that you've had quite enough\n\
\n\
Just remember that you're standing on a planet that's evolving\n\
And revolving at nine hundred miles an hour\n\
That's orbiting at nineteen miles a second, so it's reckoned\n\
A sun that is the source of all our power\n\
\n\
The sun and you and me and all the stars that we can see\n\
Are moving at a million miles a day\n\
In an outer spiral arm, at forty thousand miles an hour\n\
Of the galaxy we call the 'milky way'\n\
\n\
Our galaxy itself contains a hundred billion stars\n\
It's a hundred thousand light years side to side\n\
It bulges in the middle, sixteen thousand light years thick\n\
But out by us, it's just three thousand light years wide\n\
\n\
We're thirty thousand light years from galactic central point\n\
We go 'round every two hundred million years\n\
And our galaxy is only one of millions of billions\n\
In this amazing and expanding universe\n\
\n\
The universe itself keeps on expanding and expanding\n\
In all of the directions it can whizz\n\
As fast as it can go, the speed of light, you know\n\
Twelve million miles a minute and that's the fastest speed there is\n\
\n\
So remember, when you're feeling very small and insecure\n\
How amazingly unlikely is your birth\n\
And pray that there's intelligent life somewhere up in space\n\
'Cause it's bugger all down here on Earth\n\
";

DataGenStatus_t FillArray(uint8_t* arr, int size) {
    if (arr == 0) {
        return DG_Err_NullPtr;
    }

    if (size > sizeof(data) || size <= 0) {
        return DG_Err_InvalidSize;
    }

    for (int i = 0; i < (size - 1); i++) {
        arr[i] = data[i];
    }

    arr[size] = '\0';

    return DG_Ok;
}

int GetMaxDataSize() {
    return sizeof(data);
}
