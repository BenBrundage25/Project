import { Hono } from 'hono';
//import { pool } from '../db/index';

const contacts = new Hono();


contacts.get('/', async (c) => {

});


contacts.post('/', async (c) => {

});

export default contacts;