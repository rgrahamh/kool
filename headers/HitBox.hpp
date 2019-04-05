class HitBox{
	public:
	    Object *parent;
	    int offsetX;
	    int offsetY;
	    int width;
	    int height;
	    float ttl;

	    HitBox(int offsetX, int offsetY, int width, int height, float ttl=-1);
	    float decTime(float delta); //(if ttl > 0 && ttl - delta <= 0){ttl = ttl - 1;} return ttl

}
