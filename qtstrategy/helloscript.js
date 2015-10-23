var obj = new Object;
obj.text = "script.hello"
obj.run = function(){
        logger.info("hello from script");
};
obj.debug = function(){
    debugger;
}
obj;
