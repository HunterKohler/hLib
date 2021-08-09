import casual from "casual";
import mongoose from "mongoose";

const { Schema, model } = mongoose;

export const UserSchema = new Schema({ 
    first_name: String,
    last_name: String,
    groups: [{
        type: Schema.Types.ObjectId,
        ref: "Groups"
    }],
    bio: String,
    address: {
        building_number: String,
        street: String,
        state: String,
        city: String,
        zip: String
    },
    email: String,
    password: String,
    username: String,
    date_of_birth: Date,
    website: String
}, {
    timestamps: {
        createdAt: "created",
        updatedAt: "updated"
    }
});

casual.define("user", () => {
    return new UserModel({
        first_name: casual.first_name,
        last_name: casual.last_name,
        bio: casual.description,
        address: {
            building_number: casual.building_number,
            street: casual.street,
            zip: casual.zip(),
            state: casual.state,
            city: casual.city,
        },
        email: casual.email,
        password: casual.password,
        username: casual.username,
        date_of_birth: casual.date(), 
        website: casual.url
    });
});

export const UserModel = model("Users", UserSchema);