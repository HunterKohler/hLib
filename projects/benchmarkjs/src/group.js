import casual from "casual";
import mongoose from "mongoose";

const { Schema, model } = mongoose;

const OptionsSchema = new Schema({
    role: String,
    user: {
        type: Schema.Types.ObjectId,
        ref: "Users"
    },
    share_location: Boolean,
    follow_options: Boolean
});

casual.define("options", (user) => {
    return {
        user,
        role: casual.title,
        share_location: casual.boolean,
        follow_options: casual.boolean
    }
});

const GroupSchema = new Schema({
    optionsMap: {
        type: Map,
        of: OptionsSchema
    },
    optionsArray: [OptionsSchema]
});

casual.define("group", (userIds) => {
    return new GroupModel({
        optionsMap: new Map(userIds.reduce((entries, userId) => {
            entries.push([userId, casual.options(userId)]);
            return entries;
        }, [])),
        optionsArray: userIds.map(casual.options)
    });
});

export const GroupModel = model("Groups", GroupSchema);