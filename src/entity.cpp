#include "entity.hpp"

Entity::Entity(){

}

Entity::Entity(string file_name, Vector2f scale_){
    if (!texture->loadFromFile(PICS_PATH + file_name)) {
        throw runtime_error("couldn't read sprite: " + file_name);
    }
    sprite.setTexture(*texture);
    scale = scale_;
    sprite.setScale(scale);
}

Entity::Entity(Texture* tex, Vector2f scale_){
    delete texture;
    texture = tex;
    sprite.setTexture(*texture);
    scale = scale_;
    sprite.setScale(scale);
}

void Entity::mirror_sprite_horizontally() {
    sprite.scale(-1, 1);
    if(sprite.getScale().x < 0 and sprite.getOrigin().x == 0)
        sprite.setOrigin(sprite.getLocalBounds().width - sprite.getOrigin().x, sprite.getOrigin().y);
    if(sprite.getScale().x > 0 and sprite.getOrigin().x != 0){
        sprite.setOrigin(0, sprite.getOrigin().y);
    }
}

void Entity::update_position(double left_bound, double right_bound){
    auto x = sprite.getPosition().x;
    auto y = sprite.getPosition().y;
    x += vx + ax/2;
    y += vy + ay/2;
    vy += ay;
    vx += ax;
    if(x < left_bound){
        x = left_bound;
    }
    if(x > right_bound - sprite.getGlobalBounds().width){
        x = right_bound - sprite.getGlobalBounds().width;
    }
    if(x_collision){
        x_collision = false;
        x = x_after_collision;
    }
    if(y_collision){
        y_collision = false;
        y = y_after_collision;
    }
    sprite.setPosition(x, y);
}

FloatRect Entity::apply_time_to_rect(FloatRect rect, double time){
    auto &x = rect.left;
    auto &y = rect.top;
    x += 1/2.f * ax * time * time + vx * time;
    y += 1/2.f * ay * time * time + vy * time;
    return rect;
}

FloatRect Entity::find_first_collision(FloatRect me, FloatRect terrain){
    double l = 0, r = 1;
    for(int i = 0 ; i < entity::BS_STEP_COUNTS ; i ++){
        double mid = (l + r)/2.f;
        if(apply_time_to_rect(me, mid).intersects(terrain)){
            r = mid;
        }
        else{
            l = mid;
        }   
    }
    return apply_time_to_rect(me, r);
}

FloatRect Entity::find_overlap_rect(FloatRect rect1, FloatRect rect2){
    float left = max(rect1.left, rect2.left);
    float top = max(rect1.top, rect2.top);
    float right = min(rect1.left + rect1.width, rect2.left + rect2.width);
    float bottom = min(rect1.top + rect1.height, rect2.top + rect2.height);
    return FloatRect(left, top, right - left, bottom - top);
}

bool Entity::check_top_collision(FloatRect me, FloatRect block){
    auto overlap = find_overlap_rect(me,  block);
    return me.top < block.top + block.height and overlap.width >= overlap.height
        and me.top > block.top;
}

bool Entity::check_bottom_collision(FloatRect me, FloatRect block){
    auto overlap = find_overlap_rect(me,  block);
    return me.top + me.height > block.top and overlap.width >= overlap.height
        and me.top + me.height < block.top + block.height;
}

bool Entity::check_left_collision(FloatRect me, FloatRect block){
    auto overlap = find_overlap_rect(me,  block);
    return me.left > block.left and me.left < block.left + block.width and overlap.height >= overlap.width;
}

bool Entity::check_right_collision(FloatRect me, FloatRect block){
    auto overlap = find_overlap_rect(me,  block);
    return me.left+me.width > block.left and me.left+me.width < block.left + block.width and overlap.height >= overlap.width;
}

void Entity::handle_collision(FloatRect block){ 
    FloatRect me = sprite.getGlobalBounds();
    me = find_first_collision(me, block);
    if(check_top_collision(me, block)){
        y_collision = true;
        y_after_collision = block.top + block.height;
        vy = 0;
    }
    else if(check_bottom_collision(me, block)){
        y_collision = true;
        going_up = false;
        ay = 0;
        vy = 0;
        y_after_collision = block.top - me.height;
    }
    else if(check_left_collision(me, block)){
        x_collision = true;
        x_after_collision = block.left + block.width;
    }
    else if(check_right_collision(me, block)){
        x_collision = true;
        x_after_collision = block.left - me.width;
    }
}

FloatRect Entity::get_next_frame_rect(double left_bound, double right_bound){
    auto x = sprite.getPosition().x;
    auto y = sprite.getPosition().y;
    x += vx;
    y += (vy + ay);
    if(x < left_bound){
        x = left_bound;
    }
    if(x > right_bound - sprite.getGlobalBounds().width){
        x = right_bound - sprite.getGlobalBounds().width;
    }
    auto ans = sprite.getGlobalBounds();
    ans.left = x, ans.top = y;
    return ans;
}

bool Entity::collides_with(Sprite other){
    return sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

void Entity::render(RenderWindow &window){
    window.draw(sprite);
}

Vector2f Entity::get_position(){
    return sprite.getPosition();
}

Vector2f Entity::get_center(){
    Vector2f res = sprite.getPosition();
    res.x += sprite.getGlobalBounds().width/2.f;
    res.y += sprite.getGlobalBounds().height/2.f;
    return res;
}

void Entity::set_position(double x, double y){
    sprite.setPosition(x, y);
}

Sprite Entity::get_sprite(){
    return sprite;
}

void Entity::rotate90(){
    static bool moved = false;
    if(!moved){
        moved = true;
        sprite.move(sprite.getGlobalBounds().width/2.f, sprite.getGlobalBounds().height/2.f);
    }
    IntRect texture_rect = sprite.getTextureRect();
    swap(texture_rect.width, texture_rect.height);
    sprite.setTextureRect(texture_rect);
    sprite.setOrigin(texture_rect.width/2.f, texture_rect.height/2.f);
    sprite.rotate(90.f);
}

void Entity::set_frame(IntRect frame, bool mirror){
    sprite.setTextureRect(frame);
    sprite.setScale(scale);
    if(mirror)
        mirror_sprite_horizontally();
}

FloatRect Entity::get_rect(){
    return sprite.getGlobalBounds();
}

double Entity::get_width(){
    return sprite.getGlobalBounds().width;
}

double Entity::get_height(){
    return sprite.getGlobalBounds().height;
}