1) In initialize_array.bat, it should be run only once because it only keep track of index positioning.
2) set_array.bat, we will call it to push elements again and again(its not a good way implement. . .just a simple way to start).
3) push.bat basically calls create_element.bat after deciding whether its a integer or a string.
4) create_element.bat creates element based on whether its a string or interger.

1 and 0 are flags used for differentiating between actual string and integer

(THERE IS ROOM FOR WHOLE LOT OF IMPROVEMNT,  this just my first try to implememt functionality of an generic array from scratch).
