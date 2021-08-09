import "./utils.js";
import assert from "assert";
import casual from "casual";
import { MongoMemoryServer } from "mongodb-memory-server";
import mongoose from "mongoose";
import { UserModel } from "./user.js";
import { GroupModel } from "./group.js";
import { saveAll } from "./utils.js";
import * as timer from "./timer.js"

let uri, database;

const USER_COUNT = 1000;
const GROUP_SIZE = 5;
const GROUP_COUNT = 1000;

timer.section("setup", () => {
    database = new MongoMemoryServer();
    uri = await database.getUri();
    await mongoose.connect(uri, { 
        useNewUrlParser: true, 
        useUnifiedTopology: true 
    });
})

timer.section("data", () => {
    const users = [...new Array(USER_COUNT)].map(() => casual.user);
    const groups = [...new Array(GROUP_COUNT)]
        .map(() => {
            const userIndices = [];
            while(userIndices.length < GROUP_SIZE) {
                let i = casual.integer(0,USER_COUNT - 1);
                if(!userIndices.includes(i))
                userIndices.push(i);
            }

            const group = casual.group(userIndices.map(i => users[i]._id));
            for(const i of userIndices) {
                users[i].groups.push(group._id);
            }

            return group;
        });
});


timer.section("save", () => {
    await Promise.all(users.map(u => u.save()));
    await Promise.all(groups.map(g => g.save()));
});

timer.section("teardown", () => {
    await mongoose.disconnect();
    await database.stop();
});
